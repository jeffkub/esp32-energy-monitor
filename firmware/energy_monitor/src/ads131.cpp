#include "ads131.h"

#include <stdexcept>
#include <cstring>

#include <freertos/task.h>

#define CMD_WAKEUP      (0x02)
#define CMD_STANDBY     (0x04)
#define CMD_RESET       (0x06)
#define CMD_START       (0x08)
#define CMD_STOP        (0x0A)
#define CMD_OFFSETCAL   (0x1A)
#define CMD_RDATAC      (0x10)
#define CMD_SDATAC      (0x11)
#define CMD_RDATA       (0x12)
#define CMD_RREG(x)     (0x20 | ((x) & 0x1F))
#define CMD_WREG(x)     (0x40 | ((x) & 0x1F))

#define REG_ID          0x00

ADS131::ADS131(spi_host_device_t spi, gpio_num_t cs, gpio_num_t drdy) :
    spi_dev(spi),
    cs_pin(cs),
    drdy_pin(drdy)
{
    mutex = xSemaphoreCreateMutex();
    if(mutex == NULL)
    {
        /* ERROR */
    }

    return;
}

ADS131::~ADS131()
{
    vSemaphoreDelete(mutex);

    return;
}

int ADS131::init(void)
{
    uint8_t id_reg;

    if(xSemaphoreTake(mutex, portMAX_DELAY) == pdFALSE)
    {
        return -1;
    }

    spi_device_interface_config_t spi_config =
    {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 0,
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

    if(spi_bus_add_device(spi_dev, &spi_config, &spi_handle) != ESP_OK)
    {
        goto error;
    }

    if(command(CMD_RESET))
    {
        goto error;
    }

    usleep(10);

    if(command(CMD_SDATAC))
    {
        goto error;
    }

    if(readReg(REG_ID, &id_reg, sizeof(id_reg)))
    {
        goto error;
    }

    printf("ID = %02x\n", id_reg);

    xSemaphoreGive(mutex);
    return 0;

error:
    xSemaphoreGive(mutex);
    return -1;
}

int ADS131::read(float* data, size_t channels)
{
    while(gpio_get_level(drdy_pin) == 1)
    {
        /* TODO: Block on semaphore */
    }

    if(xSemaphoreTake(mutex, portMAX_DELAY) == pdFALSE)
    {
        return -1;
    }



    xSemaphoreGive(mutex);
    return 0;

//error:
//    xSemaphoreGive(mutex);
//    return -1;
}

int ADS131::command(uint8_t cmd)
{
    spi_transaction_t trans;

    memset(&trans, 0, sizeof(trans));

    trans.flags = SPI_TRANS_USE_TXDATA;
    trans.length = 8;
    trans.tx_data[0] = cmd;

    gpio_set_level(cs_pin, 0);

    if(spi_device_transmit(spi_handle, &trans) != ESP_OK)
    {
        return -1;
    }

    usleep(2);
    gpio_set_level(cs_pin, 1);
    usleep(1);

    return 0;
}

int ADS131::readReg(uint8_t addr, void* data, size_t len)
{
    spi_transaction_t trans[3];

    memset(trans, 0, sizeof(trans));

    trans[0].flags = SPI_TRANS_USE_TXDATA;
    trans[0].length = 8;
    trans[0].tx_data[0] = CMD_RREG(addr);

    trans[1].flags = SPI_TRANS_USE_TXDATA;
    trans[1].length = 8;
    trans[1].tx_data[0] = len - 1;

    trans[2].length = len * 8;
    trans[2].rx_buffer = data;

    gpio_set_level(cs_pin, 0);

    if(spi_device_transmit(spi_handle, &trans[0]) != ESP_OK)
    {
        return -1;
    }

    /* For multibyte commands, need to wait 4 tCLK cycles between the first and
     * second bytes */
    usleep(2);

    if(spi_device_transmit(spi_handle, &trans[1]) != ESP_OK)
    {
        return -1;
    }

    if(spi_device_transmit(spi_handle, &trans[2]) != ESP_OK)
    {
        return -1;
    }

    usleep(2);
    gpio_set_level(cs_pin, 1);
    usleep(1);

    return 0;
}

int ADS131::writeReg(uint8_t addr, const void* data, size_t len)
{
    spi_transaction_t trans[3];

    memset(trans, 0, sizeof(trans));

    trans[0].flags = SPI_TRANS_USE_TXDATA;
    trans[0].length = 8;
    trans[0].tx_data[0] = CMD_WREG(addr);

    trans[1].flags = SPI_TRANS_USE_TXDATA;
    trans[1].length = 8;
    trans[1].tx_data[0] = len - 1;

    trans[2].length = len * 8;
    trans[2].tx_buffer = data;

    gpio_set_level(cs_pin, 0);

    if(spi_device_transmit(spi_handle, &trans[0]) != ESP_OK)
    {
        return -1;
    }

    /* For multibyte commands, need to wait 4 tCLK cycles between the first and
     * second bytes */
    usleep(2);

    if(spi_device_transmit(spi_handle, &trans[1]) != ESP_OK)
    {
        return -1;
    }

    if(spi_device_transmit(spi_handle, &trans[2]) != ESP_OK)
    {
        return -1;
    }

    usleep(2);
    gpio_set_level(cs_pin, 1);
    usleep(1);

    return 0;
}
