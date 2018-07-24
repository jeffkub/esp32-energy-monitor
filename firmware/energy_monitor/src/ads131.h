#ifndef _ADS131_H_
#define _ADS131_H_

#include <cstdint>
#include <cstdlib>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>

class ADC
{
public:
    virtual void start(void) = 0;
    virtual void stop(void) = 0;

    virtual void read(float* data, size_t channels) = 0;
};

class ADS131 : public ADC
{
public:
    enum DataRate
    {
        /* DataRate_16bit_64ksps = 0, 16 bit not supported */
        /* DataRate_16bit_32ksps = 1, 16 bit not supported */
        DataRate_24bit_16ksps = 2,
        DataRate_24bit_8ksps = 3,
        DataRate_24bit_4ksps = 4,
        DataRate_24bit_2ksps = 5,
        DataRate_24bit_1ksps = 6
    };

    enum VRef
    {
        VRef_External = 0,
        VRef_Internal_2_4V = 1,
        VRef_Internal_4V = 2
    };

    ADS131(spi_host_device_t spi, gpio_num_t cs, gpio_num_t drdy);
    ~ADS131();

    void init(void);

    void setVRef(VRef config);
    void setDataRate(enum DataRate rate);

    virtual void start(void);
    virtual void stop(void);

    virtual void read(float* data, size_t channels);

private:
    spi_host_device_t spi_dev;
    spi_device_handle_t spi_handle;
    gpio_num_t cs_pin;
    gpio_num_t drdy_pin;

    SemaphoreHandle_t mutex;
    SemaphoreHandle_t drdy_sem;

    static void drdyIrqHandler(void* arg);

    void command(uint8_t cmd);
    uint8_t readReg(uint8_t addr);
    void writeReg(uint8_t addr, uint8_t val);
};

#endif /* #ifndef _ADS131_H_ */
