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
    ADS131(spi_host_device_t spi, gpio_num_t cs, gpio_num_t drdy);
    ~ADS131();

    void init(void);

    void read(float* data, size_t channels);

private:
    spi_host_device_t spi_dev;
    spi_device_handle_t spi_handle;
    gpio_num_t cs_pin;
    gpio_num_t drdy_pin;
    gpio_isr_handle_t drdy_isr_handle;

    SemaphoreHandle_t mutex;
    SemaphoreHandle_t drdy_sem;

    static void drdy_irq_handler(void* arg);

    void command(uint8_t cmd);
    void readReg(uint8_t addr, void* data, size_t len);
    void writeReg(uint8_t addr, const void* data, size_t len);
};

#endif /* #ifndef _ADS131_H_ */
