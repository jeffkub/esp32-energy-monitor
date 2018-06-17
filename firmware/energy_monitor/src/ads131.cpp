#include "ads131.h"

#include <freertos/task.h>

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

void ADS131::regRead(uint8_t addr, void* data, size_t len)
{
    spi_transaction_t trans[2];

    trans[0].length = 2;
    trans[0].flags = SPI_TRANS_USE_TXDATA;
    trans[0].tx_data[0] = 0x20 | (addr & 0x1F);
    trans[0].tx_data[1] = (len - 1) & 0x1F;

    trans[1].length = len;
    trans[1].flags = 0;
    trans[1].rx_buffer = data;

    gpio_set_level(cs_pin, 0);

    gpio_set_level(cs_pin, 1);

    return;
}

void ADS131::regWrite(uint8_t addr, const void* data, size_t len)
{
    gpio_set_level(cs_pin, 0);

    gpio_set_level(cs_pin, 1);

    return;
}
