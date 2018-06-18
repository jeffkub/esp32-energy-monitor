#include "ads131.h"

#include <stdexcept>

#include <freertos/task.h>

#define CMD_READ    0x20
#define CMD_WRITE   0x40

#define REG_ID      0x00

ADS131::ADS131(spi_host_device_t spi, gpio_num_t cs) :
    spi_dev(spi),
    cs_pin(cs)
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

    spi_device_interface_config_t spi_config =
    {
        .command_bits = 16,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 0,
        .duty_cycle_pos = 0,
        .cs_ena_pretrans = 0,
        .cs_ena_posttrans = 0,
        .clock_speed_hz = 20000000,
        .spics_io_num = cs_pin,
        .flags = 0,
        .queue_size = 2,
        .pre_cb = NULL,
        .post_cb = NULL
    };

    if(spi_bus_add_device(spi_dev, &spi_config, &spi_handle) != ESP_OK)
    {
        return -1;
    }

    if(regRead(REG_ID, &id_reg, sizeof(id_reg)))
    {
        return -1;
    }

    printf("ID = %02x\n", id_reg);

    return 0;
}

int ADS131::regRead(uint8_t addr, void* data, size_t len)
{
    spi_transaction_t trans;

    trans.flags = 0;
    trans.cmd = CMD_READ | (addr & 0x1F) |
                (((len - 1) & 0x1F) << 8);
    trans.addr = 0;
    trans.length = len;
    trans.rxlength = 0;
    trans.user = NULL;
    trans.tx_buffer = NULL;
    trans.rx_buffer = data;

    if(spi_device_transmit(spi_handle, &trans) != ESP_OK)
    {
        return -1;
    }

    return 0;
}

int ADS131::regWrite(uint8_t addr, const void* data, size_t len)
{
    spi_transaction_t trans;

    trans.flags = 0;
    trans.cmd = CMD_WRITE | (addr & 0x1F) |
                (((len - 1) & 0x1F) << 8);
    trans.addr = 0;
    trans.length = len;
    trans.rxlength = 0;
    trans.user = NULL;
    trans.tx_buffer = data;
    trans.rx_buffer = NULL;

    if(spi_device_transmit(spi_handle, &trans) != ESP_OK)
    {
        return -1;
    }

    return 0;
}
