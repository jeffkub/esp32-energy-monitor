#ifndef _ESP32_SPI_H_
#define _ESP32_SPI_H_

#include <cstdint>
#include <cstdlib>

#include <soc/spi_struct.h>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class ESP32SPI
{
public:
    ESP32SPI(volatile void* device,  unsigned irq);
    ~ESP32SPI();

    void init(void);

    void setClock(unsigned freq);

    void transfer(void* tx_data, size_t tx_len, void* rx_data, size_t rx_len);

private:
    volatile void* hw;
    unsigned irq_num;

    SemaphoreHandle_t mutex;
    SemaphoreHandle_t done_sem;

    intr_handle_t intr_handle;

    static void spiIrqHandler(void* arg);
};

#endif /* #ifndef _ESP32_SPI_H_ */
