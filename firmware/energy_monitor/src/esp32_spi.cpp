#include "esp32_spi.h"

#include <cassert>

#define SPI_CTRL_REG        0x08
#define SPI_CTRL1_REG       0x0C
#define SPI_CTRL2_REG       0x14
#define SPI_CLOCK_REG       0x18
#define SPI_USER_REG        0x1C
#define SPI_PIN_REG         0x34

ESP32SPI::ESP32SPI(uint32_t device) :
    base_reg(device)
{
    mutex = xSemaphoreCreateMutex();
    assert(mutex != NULL);
}

ESP32SPI::~ESP32SPI()
{
    vSemaphoreDelete(mutex);
}

void ESP32SPI::init(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    writeReg(SPI_CTRL_REG, 0x200000);

    xSemaphoreGive(mutex);
}

void ESP32SPI::setClock(unsigned freq)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    xSemaphoreGive(mutex);
}

void ESP32SPI::transfer(void* tx_buf, void* rx_buf, size_t len)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    xSemaphoreGive(mutex);
}
