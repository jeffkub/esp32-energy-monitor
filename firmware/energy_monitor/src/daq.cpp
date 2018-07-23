#include "daq.h"

#include <cassert>

#include "ads131.h"

DAQ::DAQ(ADC* adc) :
    adc_dev(adc)
{

}

DAQ::~DAQ()
{

}

void DAQ::start(void)
{
    assert(xTaskCreate(&taskEntry, "daq", 4096, this, 5, &task) == pdPASS);
}

void DAQ::taskEntry(void *arg)
{
    DAQ* inst = (DAQ*)arg;

    inst->mainLoop();
}

#define SAMPLE_COUNT 1000
#define CHANNEL_COUNT 8

static float buffer[SAMPLE_COUNT][CHANNEL_COUNT];

void DAQ::mainLoop(void)
{
    while(true)
    {
        adc_dev->start();

        vTaskDelay(500 / portTICK_PERIOD_MS);

        printf("Capture start\r\n");

        for(int index = 0; index < SAMPLE_COUNT; index++)
        {
            adc_dev->read(&buffer[index][0], CHANNEL_COUNT);
        }

        printf("Capture complete\r\n");

        adc_dev->stop();

        for(int index = 0; index < SAMPLE_COUNT; index++)
        {
            for(int chan = 0; chan < CHANNEL_COUNT; chan++)
            {
                printf("%0.9f, ", buffer[index][chan]);
            }

            printf("\r\n");

            if(index % 100 == 0)
            {
                vTaskDelay(1);
            }
        }

        vTaskSuspend(NULL);
    }
}
