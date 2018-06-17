#ifndef _ADS131_H_
#define _ADS131_H_

#include <stdint.h>
#include <stdlib.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

class ADS131
{
public:
    ADS131(spi_host_device_t spi, gpio_num_t cs);
    ~ADS131();

private:
    spi_host_device_t spi_dev;
    gpio_num_t cs_pin;

    SemaphoreHandle_t mutex;

    void regRead(uint8_t addr, void* data, size_t len);
    void regWrite(uint8_t addr, const void* data, size_t len);
};

#endif /* #ifndef _ADS131_H_ */
