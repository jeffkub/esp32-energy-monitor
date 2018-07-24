#include <cassert>
#include <cstdlib>
#include <cstdio>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/periph_ctrl.h>
#include <driver/spi_master.h>
#include <soc/io_mux_reg.h>

#include "platform.h"
#include "ads131.h"
#include "daq.h"
#include "esp32_spi.h"

static void platformInit(void);
static void blinkTask(void *arg);

static ESP32SPI spi(&SPI2, ETS_SPI2_INTR_SOURCE);
static ADS131 adc(HSPI_HOST, CS_PIN, ADC_DRDY_PIN);
static DAQ daq(&adc);

static void platformInit(void)
{
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_IRAM));

    /* GPIO configuration */
    gpio_pad_select_gpio(LED1_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(LED1_PIN, 0));

    gpio_pad_select_gpio(LED2_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(LED2_PIN, 0));

    gpio_pad_select_gpio(LED3_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(LED3_PIN, 0));

    gpio_pad_select_gpio(CS_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(CS_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(CS_PIN, 1));

    gpio_pad_select_gpio(ADC_RESET_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(ADC_RESET_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(ADC_RESET_PIN, 1));

    gpio_pad_select_gpio(ADC_PWDN_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(ADC_PWDN_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(ADC_PWDN_PIN, 1));

    gpio_pad_select_gpio(ADC_START_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(ADC_START_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(ADC_START_PIN, 0));

    gpio_pad_select_gpio(ADC_DRDY_PIN);
    ESP_ERROR_CHECK(gpio_set_direction(ADC_DRDY_PIN, GPIO_MODE_INPUT));

    /* SPI configuration */
/*
    const spi_bus_config_t spi_bus_config =
    {
        .mosi_io_num = MOSI_PIN,
        .miso_io_num = MISO_PIN,
        .sclk_io_num = SCK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0
    };

    ESP_ERROR_CHECK(spi_bus_initialize(HSPI_HOST, &spi_bus_config, 0));
*/
    periph_module_enable(PERIPH_HSPI_MODULE);

    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[MOSI_PIN], PIN_FUNC_GPIO);
    gpio_set_direction(MOSI_PIN, GPIO_MODE_INPUT_OUTPUT);
    gpio_matrix_out(MOSI_PIN, HSPID_OUT_IDX, false, false);
    gpio_matrix_in(MOSI_PIN, HSPID_IN_IDX, false);

    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[MISO_PIN], PIN_FUNC_GPIO);
    gpio_set_direction(MISO_PIN, GPIO_MODE_INPUT_OUTPUT);
    gpio_matrix_out(MISO_PIN, HSPIQ_OUT_IDX, false, false);
    gpio_matrix_in(MISO_PIN, HSPIQ_IN_IDX, false);

    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[SCK_PIN], PIN_FUNC_GPIO);
    gpio_set_direction(SCK_PIN, GPIO_MODE_INPUT_OUTPUT);
    gpio_matrix_out(SCK_PIN, HSPICLK_OUT_IDX, false, false);
    gpio_matrix_in(SCK_PIN, HSPICLK_IN_IDX, false);

    spi.init();

    uint8_t data[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};

    ESP_ERROR_CHECK(gpio_set_level(CS_PIN, 0));
    spi.transfer(data, sizeof(data), data, sizeof(data));
    ESP_ERROR_CHECK(gpio_set_level(CS_PIN, 1));

    printf("rx data: %02x %02x %02x %02x\r\n", data[0], data[1], data[2], data[3]);

    vTaskSuspend(NULL);

    /* Driver initialization */
    adc.init();
    adc.setVRef(ADS131::VRef_Internal_4V);
    adc.setDataRate(ADS131::DataRate_24bit_16ksps);
}

static void blinkTask(void *arg)
{
    while(1)
    {
        gpio_set_level(LED1_PIN, 1);
        vTaskDelay(250 / portTICK_PERIOD_MS);

        gpio_set_level(LED1_PIN, 0);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main()
{
    printf("Program start\n");

    platformInit();

    assert(xTaskCreate(&blinkTask, "blinkTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL) == pdPASS);

    daq.start();
}
