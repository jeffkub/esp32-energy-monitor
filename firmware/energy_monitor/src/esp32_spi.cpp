#include "esp32_spi.h"

#include <cassert>
#include <climits>

#include <soc/spi_struct.h>

#define SPI_REG(inst)   (*((volatile spi_dev_t*)((inst)->reg_base)))

#define CLKDIV_PRE_MAX  (1 << 13)
#define CLKCNT_N_MAX    (1 << 6)

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
    reg_base(device),
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

    SPI_REG(this).ctrl2.setup_time = 8;
    SPI_REG(this).ctrl2.hold_time = 8;

    SPI_REG(this).user.usr_command = 0;
    SPI_REG(this).user.usr_addr = 0;
    SPI_REG(this).user.usr_miso = 1;
    SPI_REG(this).user.usr_mosi = 1;
    SPI_REG(this).user.cs_setup = 1;
    SPI_REG(this).user.cs_hold = 1;
    SPI_REG(this).user.doutdin = 0;

    xSemaphoreGive(mutex);
}

void ESP32SPI::setClock(unsigned freq)
{
    int best_err = INT_MAX;
    int pre = CLKDIV_PRE_MAX;
    int n = CLKCNT_N_MAX;

    if(freq >= APB_CLK_FREQ)
    {
        pre = 1;
        n = 1;
    }
    else
    {
        for(int cur_n = 2; cur_n <= CLKCNT_N_MAX; cur_n++)
        {
            /* Round up value */
            int cur_pre = (APB_CLK_FREQ + (cur_n * freq) - 1) / (cur_n * freq);

            if(cur_pre < 1) cur_pre = 1;
            if(cur_pre > CLKDIV_PRE_MAX) continue;

            int cur_freq = APB_CLK_FREQ / (cur_n * cur_pre);
            int err = abs(freq - cur_freq);

            if(err <= best_err)
            {
                best_err = err;
                pre = cur_pre;
                n = cur_n;
            }
        }
    }

    xSemaphoreTake(mutex, portMAX_DELAY);

    if(pre == 1 && n == 1)
    {
        SPI_REG(this).clock.clk_equ_sysclk = 1;
        SPI_REG(this).clock.clkdiv_pre = 0;
        SPI_REG(this).clock.clkcnt_n = 0;
        SPI_REG(this).clock.clkcnt_h = 0;
        SPI_REG(this).clock.clkcnt_l = 0;
    }
    else
    {
        SPI_REG(this).clock.clk_equ_sysclk = 0;
        SPI_REG(this).clock.clkdiv_pre = pre - 1;
        SPI_REG(this).clock.clkcnt_n = n-1;
        SPI_REG(this).clock.clkcnt_h = (n/2)-1;
        SPI_REG(this).clock.clkcnt_l = n-1;
    }

    xSemaphoreGive(mutex);
}

void ESP32SPI::transfer(void* tx_data, size_t tx_len, void* rx_data, size_t rx_len)
{
    xSemaphoreTake(mutex, portMAX_DELAY);

    /* Configure SPI transaction */
    SPI_REG(this).mosi_dlen.usr_mosi_dbitlen = tx_len * 8;
    SPI_REG(this).miso_dlen.usr_miso_dbitlen = rx_len * 8;

    /* Write TX data to SPI data buffer */
    for(int index = 0; index < (tx_len+3)/4; index++)
    {
        /* TODO: Handle non-word aligned lengths */
        SPI_REG(this).data_buf[index] = ((uint32_t*)tx_data)[index];
    }

    /* Start SPI transaction */
    SPI_REG(this).cmd.usr = 1;

    /* Wait for transaction to complete */
    while(SPI_REG(this).cmd.usr)
    {
        esp_intr_enable(intr_handle);
        xSemaphoreTake(done_sem, portMAX_DELAY);
    }

    if(rx_data != NULL)
    {
        for(int index = 0; index < (tx_len+3)/4; index++)
        {
            /* TODO: Handle non-word aligned lengths */
            ((uint32_t*)rx_data)[index] = SPI_REG(this).data_buf[index];
        }
    }

    xSemaphoreGive(mutex);
}
