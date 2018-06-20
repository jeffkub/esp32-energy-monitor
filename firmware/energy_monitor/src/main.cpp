#include <stdlib.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <soc/io_mux_reg.h>

#include "platform.h"
#include "ads131.h"

static int platformInit(void);
static void blinkTask(void *arg);

ADS131 adc(HSPI_HOST, CS_PIN, ADC_DRDY_PIN);

static int platformInit(void)
{
    /* GPIO configuration */
    gpio_pad_select_gpio(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED1_PIN, 0);

    gpio_pad_select_gpio(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED2_PIN, 0);

    gpio_pad_select_gpio(LED3_PIN);
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED3_PIN, 0);

    gpio_pad_select_gpio(CS_PIN);
    gpio_set_direction(CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(CS_PIN, 1);

    gpio_pad_select_gpio(ADC_RESET_PIN);
    gpio_set_direction(ADC_RESET_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ADC_RESET_PIN, 1);

    gpio_pad_select_gpio(ADC_PWDN_PIN);
    gpio_set_direction(ADC_PWDN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ADC_PWDN_PIN, 1);

    gpio_pad_select_gpio(ADC_START_PIN);
    gpio_set_direction(ADC_START_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ADC_START_PIN, 0);

    gpio_pad_select_gpio(ADC_DRDY_PIN);
    gpio_set_direction(ADC_DRDY_PIN, GPIO_MODE_INPUT);

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

    if(spi_bus_initialize(HSPI_HOST, &spi_bus_config, 0) != ESP_OK)
    {
        return -1;
    }

    /* Driver initialization */
    if(adc.init())
    {
        return -1;
    }

    return 0;
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

    return;
}

extern "C" void app_main()
{
    printf("Program start\n");

    platformInit();

    xTaskCreate(&blinkTask, "blinkTask", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    return;
}
