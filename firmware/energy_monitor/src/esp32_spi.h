#ifndef _ESP32_SPI_H_
#define _ESP32_SPI_H_

#include <cstdlib>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class ESP32SPI
{
public:
    ESP32SPI(uint32_t device);
    ~ESP32SPI();

    void init(void);

    void setClock(unsigned freq);

    void transfer(void* tx_buf, void* rx_buf, size_t len);

private:
    uint32_t base_reg;

    SemaphoreHandle_t mutex;

    inline uint32_t readReg(uint32_t reg)
    {
        return *((uint32_t*)(this->base_reg + reg));
    }

    inline void writeReg(uint32_t reg, uint32_t val)
    {
        *((uint32_t*)(this->base_reg + reg)) = val;
    }
};

#endif /* #ifndef _ESP32_SPI_H_ */
