#include "ads131.h"

#include <cassert>
#include <unistd.h>

#include <freertos/task.h>

#define CMD_NOP             (0x00)
#define CMD_WAKEUP          (0x02)
#define CMD_STANDBY         (0x04)
#define CMD_RESET           (0x06)
#define CMD_START           (0x08)
#define CMD_STOP            (0x0A)
#define CMD_OFFSETCAL       (0x1A)
#define CMD_RDATAC          (0x10)
#define CMD_SDATAC          (0x11)
#define CMD_RDATA           (0x12)
#define CMD_RREG(reg)       (0x20 | ((reg) & 0x1F))
#define CMD_WREG(reg)       (0x40 | ((reg) & 0x1F))

#define REG_ID              (0x00)
#define REG_CONFIG1         (0x01)
#define REG_CONFIG2         (0x02)
#define REG_CONFIG3         (0x03)
#define REG_FAULT           (0x04)
#define REG_CHnSET(n)       (0x05 + (n))
#define REG_FAULT_STATP     (0x12)
#define REG_FAULT_STATN     (0x13)
#define REG_GPIO            (0x14)

#define CONFIG1_DR(x)       ((x) << 0)
#define CONFIG1_DR_MASK     (0x7 << 0)

#define CONFIG3_PDB_REFBUF  (  1 << 7)
#define CONFIG3_VREF_4V     (  1 << 5)

#define BITS_PER_CHAN       24
#define MAX_CHANS           8

static inline int32_t sign_extend(int32_t x, int bits)
{
    int32_t m = 1 << (bits - 1);
    return (x ^ m) - m;
}

void IRAM_ATTR ADS131::drdy_irq_handler(void* arg)
{
    ADS131* inst = (ADS131*)arg;
    BaseType_t do_yield = pdFALSE;

    xSemaphoreGiveFromISR(inst->drdy_sem, &do_yield);

    if(do_yield)
    {
        portYIELD_FROM_ISR();
    }
}

ADS131::ADS131(spi_host_device_t spi, gpio_num_t cs, gpio_num_t drdy) :
    spi_dev(spi),
    cs_pin(cs),
    drdy_pin(drdy)
{
    mutex = xSemaphoreCreateMutex();
    assert(mutex != NULL);

    drdy_sem = xSemaphoreCreateBinary();
    assert(drdy_sem != NULL);
}

ADS131::~ADS131()
{
    vSemaphoreDelete(mutex);
    vSemaphoreDelete(drdy_sem);
}

void ADS131::init(void)
{
    uint8_t id_reg;

    xSemaphoreTake(mutex, portMAX_DELAY);

    /* Setup interrupt handler for DRDY pin */
    ESP_ERROR_CHECK(gpio_set_intr_type(drdy_pin, GPIO_INTR_NEGEDGE));
    ESP_ERROR_CHECK(gpio_isr_handler_add(drdy_pin, drdy_irq_handler, this));

    spi_device_interface_config_t spi_config =
    {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 1,
        .duty_cycle_pos = 0,
        .cs_ena_pretrans = 0,
        .cs_ena_posttrans = 0,
        .clock_speed_hz = 20000000,
        .spics_io_num = -1,
        .flags = 0,
        .queue_size = 2,
        .pre_cb = NULL,
        .post_cb = NULL
    };

    ESP_ERROR_CHECK(spi_bus_add_device(spi_dev, &spi_config, &spi_handle));

    /* Issue reset command */
    command(CMD_RESET);
    usleep(10);

    /* By default the device is in read data continuous mode, cancel it */
    command(CMD_SDATAC);
    usleep(2);

    /* Check the device ID register */
    id_reg = readReg(REG_ID);
    assert(id_reg == 0xD2);

    xSemaphoreGive(mutex);
}

void ADS131::setVRef(VRef config)
{
    uint8_t reg;

    xSemaphoreTake(mutex, portMAX_DELAY);

    reg = readReg(REG_CONFIG3);

    /* Enable the internal reference buffer for a internal vref */
    reg &= ~CONFIG3_PDB_REFBUF;
    reg |= (config == VRef_External) ? 0 : CONFIG3_PDB_REFBUF;

    /* Internal vref voltage */
    reg &= ~CONFIG3_VREF_4V;
    reg |= (config == VRef_Internal_4V) ? CONFIG3_VREF_4V : 0;

    writeReg(REG_CONFIG3, reg);

    xSemaphoreGive(mutex);

    /* Wait for VREF startup time */
    vTaskDelay(150 / portTICK_PERIOD_MS);
}

void ADS131::setDataRate(enum DataRate rate)
{
    uint8_t reg;

    xSemaphoreTake(mutex, portMAX_DELAY);

    reg = readReg(REG_CONFIG1);
    reg &= ~CONFIG1_DR_MASK;
    reg |= CONFIG1_DR((uint8_t)rate);
    writeReg(REG_CONFIG1, reg);

    xSemaphoreGive(mutex);
}

void ADS131::start(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    command(CMD_START);
    xSemaphoreGive(mutex);
}

void ADS131::stop(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    command(CMD_STOP);
    xSemaphoreGive(mutex);
}

void ADS131::read(float* data, size_t channels)
{
    spi_transaction_t trans = {};
    uint8_t buffer[28] = {};

    assert(channels <= MAX_CHANS);

    trans.length = sizeof(buffer) * 8;
    trans.tx_buffer = buffer;
    trans.rx_buffer = buffer;

    buffer[0] = CMD_RDATA; /* Command byte */

    xSemaphoreTake(mutex, portMAX_DELAY);

    /* Wait for DRDY pin to go low */
    while(gpio_get_level(drdy_pin) == 1)
    {
        xSemaphoreGive(mutex);
        xSemaphoreTake(drdy_sem, portMAX_DELAY);
        xSemaphoreTake(mutex, portMAX_DELAY);
    }

    /* Perform SPI transfer */
    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 0));
    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &trans));
    usleep(2);
    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 1));

    /* Process channel data */
    for(unsigned chan = 0; chan < channels; chan++)
    {
        uint8_t* cur_sample = &buffer[4 + (chan*3)];

        /* Sign extend 24 bit integer to 32 bit integer */
        int32_t raw_val = sign_extend(
            ((int32_t)cur_sample[0]) << 16 |
            ((int32_t)cur_sample[1]) <<  8 |
            ((int32_t)cur_sample[2]) <<  0, BITS_PER_CHAN);

        /* Convert to float and scale to +/-1 range */
        data[chan] = (float)raw_val / (float)(1 << (BITS_PER_CHAN-1));
    }

    xSemaphoreGive(mutex);
}

void ADS131::command(uint8_t cmd)
{
    spi_transaction_t trans = {};

    trans.flags = SPI_TRANS_USE_TXDATA;
    trans.length = 8;
    trans.tx_data[0] = cmd;

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 0));

    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &trans));
    usleep(2);

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 1));
    usleep(1);
}

uint8_t ADS131::readReg(uint8_t addr)
{
    spi_transaction_t cmd = {};
    spi_transaction_t len = {};
    spi_transaction_t data = {};

    cmd.flags = SPI_TRANS_USE_TXDATA;
    cmd.length = 8;
    cmd.tx_data[0] = CMD_RREG(addr);

    len.flags = SPI_TRANS_USE_TXDATA;
    len.length = 8;
    len.tx_data[0] = 0; /* Len - 1 */

    data.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
    data.length = 8;
    data.tx_data[0] = CMD_NOP;

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 0));

    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &cmd))
    usleep(2);
    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &len));
    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &data));
    usleep(2);

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 1));
    usleep(1);

    return data.rx_data[0];
}

void ADS131::writeReg(uint8_t addr, uint8_t val)
{
    spi_transaction_t cmd = {};
    spi_transaction_t len = {};
    spi_transaction_t data = {};

    cmd.flags = SPI_TRANS_USE_TXDATA;
    cmd.length = 8;
    cmd.tx_data[0] = CMD_WREG(addr);       /* Command */

    len.flags = SPI_TRANS_USE_TXDATA;
    len.length = 8;
    len.tx_data[0] = 0;                    /* Len - 1 */

    data.flags = SPI_TRANS_USE_TXDATA;
    data.length = 8;
    data.tx_data[0] = val;

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 0));

    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &cmd));
    usleep(2);
    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &len));
    ESP_ERROR_CHECK(spi_device_transmit(spi_handle, &data));
    usleep(2);

    ESP_ERROR_CHECK(gpio_set_level(cs_pin, 1));
    usleep(1);
}
