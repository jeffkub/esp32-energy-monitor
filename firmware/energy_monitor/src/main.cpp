#include <stdlib.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <driver/gpio.h>
#include <soc/io_mux_reg.h>

#include "ads131.h"

#define LED1_PIN GPIO_NUM_18
#define LED2_PIN GPIO_NUM_19
#define LED3_PIN GPIO_NUM_21

ADS131 adc();

void blink_task(void *arg)
{
    printf("Program start\n");

    gpio_pad_select_gpio(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);

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
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    return;
}
