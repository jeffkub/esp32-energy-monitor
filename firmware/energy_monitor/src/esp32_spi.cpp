#include "esp32_spi.h"

#include <cassert>

void IRAM_ATTR ESP32SPI::spiIrqHandler(void* arg)
{
    ESP32SPI* inst = (ESP32SPI*)arg;
    BaseType_t do_yield = pdFALSE;

    esp_intr_disable(inst->intr_handle);
    xSemaphoreGiveFromISR(inst->done_sem, &do_yield);

    if(do_yield)
    {
        portYIELD_FROM_ISR();
    }
}

ESP32SPI::ESP32SPI(volatile void* device,  unsigned irq) :
    hw(device),
    irq_num(irq)
{
    mutex = xSemaphoreCreateMutex();
    assert(mutex != NULL);

    done_sem = xSemaphoreCreateBinary();
    assert(done_sem != NULL);
}

ESP32SPI::~ESP32SPI()
{
    vSemaphoreDelete(mutex);
    vSemaphoreDelete(done_sem);
}

void ESP32SPI::init(void)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    ESP_ERROR_CHECK(esp_intr_alloc(irq_num, ESP_INTR_FLAG_INTRDISABLED | ESP_INTR_FLAG_IRAM, spiIrqHandler, this, &intr_handle));

    ((volatile spi_dev_t*)hw)->ctrl2.setup_time = 8;
    ((volatile spi_dev_t*)hw)->ctrl2.hold_time = 8;

    ((volatile spi_dev_t*)hw)->user.usr_command = 0;
    ((volatile spi_dev_t*)hw)->user.usr_addr = 0;
    ((volatile spi_dev_t*)hw)->user.usr_miso = 1;
    ((volatile spi_dev_t*)hw)->user.usr_mosi = 1;
    ((volatile spi_dev_t*)hw)->user.cs_setup = 1;
    ((volatile spi_dev_t*)hw)->user.cs_hold = 1;
    ((volatile spi_dev_t*)hw)->user.doutdin = 0;

    xSemaphoreGive(mutex);
}

void ESP32SPI::setClock(unsigned freq)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    ((volatile spi_dev_t*)hw)->clock.clk_equ_sysclk = 0;
    ((volatile spi_dev_t*)hw)->clock.clkdiv_pre = 0;
    ((volatile spi_dev_t*)hw)->clock.clkcnt_n = 3;
    ((volatile spi_dev_t*)hw)->clock.clkcnt_h = (((volatile spi_dev_t*)hw)->clock.clkcnt_n + 1) / 2 - 1;
    ((volatile spi_dev_t*)hw)->clock.clkcnt_l = ((volatile spi_dev_t*)hw)->clock.clkcnt_n;

    xSemaphoreGive(mutex);
}

void ESP32SPI::transfer(void* tx_data, size_t tx_len, void* rx_data, size_t rx_len)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    /* Configure SPI transaction */
    ((volatile spi_dev_t*)hw)->mosi_dlen.usr_mosi_dbitlen = tx_len * 8;
    ((volatile spi_dev_t*)hw)->miso_dlen.usr_miso_dbitlen = rx_len * 8;

    /* Write TX data to SPI data buffer */
    for(int index = 0; index < (tx_len+3)/4; index++)
    {
        /* TODO: Handle non-word aligned lengths */
        ((volatile spi_dev_t*)hw)->data_buf[index] = ((uint32_t*)tx_data)[index];
    }

    /* Start SPI transaction */
    ((volatile spi_dev_t*)hw)->cmd.usr = 1;

    /* Wait for transaction to complete */
    while(((volatile spi_dev_t*)hw)->cmd.usr)
    {
        esp_intr_enable(intr_handle);
        xSemaphoreTake(done_sem, portMAX_DELAY);
    }

    if(rx_data != NULL)
    {
        for(int index = 0; index < (tx_len+3)/4; index++)
        {
            /* TODO: Handle non-word aligned lengths */
            ((uint32_t*)rx_data)[index] = ((volatile spi_dev_t*)hw)->data_buf[index];
        }
    }

    xSemaphoreGive(mutex);
}
