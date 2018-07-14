#include <cassert>
#include <cstdlib>
#include <cstdio>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <soc/io_mux_reg.h>

#include "platform.h"
#include "ads131.h"

static void platformInit(void);
static void blinkTask(void *arg);
static void adcTestTask(void *arg);

static ADS131 adc(HSPI_HOST, CS_PIN, ADC_DRDY_PIN);

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

#define SAMPLE_COUNT 1000
#define CHANNEL_COUNT 8

static float buffer[SAMPLE_COUNT][CHANNEL_COUNT];

static void adcTestTask(void *arg)
{
    while(1)
    {
        for(int index = 0; index < SAMPLE_COUNT; index++)
        {
            adc.read(&buffer[index][0], CHANNEL_COUNT);
        }

        for(int index = 0; index < SAMPLE_COUNT; index++)
        {
            for(int chan = 0; chan < CHANNEL_COUNT; chan++)
            {
                printf("%0.10f, ", buffer[index][chan]);
            }

            printf("\r\n");
        }

        vTaskSuspend(NULL);
    }
}

extern "C" void app_main()
{
    printf("Program start\n");

    platformInit();

    assert(xTaskCreate(&blinkTask, "blinkTask", configMINIMAL_STACK_SIZE, NULL, 5, NULL) == pdPASS);
    assert(xTaskCreate(&adcTestTask, "adcTestTask", configMINIMAL_STACK_SIZE, NULL, 5, NULL) == pdPASS);
}
