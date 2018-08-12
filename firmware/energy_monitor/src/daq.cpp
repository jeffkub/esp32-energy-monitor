#include "daq.h"

#include <cassert>

#include "ads131.h"

#define CHANNEL_COUNT 8

DAQ::DAQ(ADC* adc, unsigned interval) :
    adc_dev(adc),
    interval_len(interval)
{
    ready_sem = xSemaphoreCreateBinary();
    assert(ready_sem != NULL);
}

DAQ::~DAQ()
{
    vSemaphoreDelete(ready_sem);
}

void DAQ::start(void)
{
    assert(xTaskCreate(&taskEntry, "sampleTask", 4096, this, configMAX_PRIORITIES - 1, &task) == pdPASS);
}

void DAQ::wait(void)
{
    xSemaphoreTake(ready_sem, portMAX_DELAY);
}

void DAQ::taskEntry(void *arg)
{
    DAQ* inst = (DAQ*)arg;

    inst->mainLoop();
}

void DAQ::mainLoop(void)
{
    float buffer[CHANNEL_COUNT];

    adc_dev->start();

    while(true)
    {
        for(unsigned sample = 0; sample < interval_len; sample++)
        {
            adc_dev->read(buffer, CHANNEL_COUNT);

            V1Rms.input(buffer[7]);
            V1Rms.input(buffer[6]);

            I1Rms.input(buffer[5]);
            I2Rms.input(buffer[4]);
            I3Rms.input(buffer[3]);
            I4Rms.input(buffer[2]);
            I5Rms.input(buffer[1]);
            I6Rms.input(buffer[0]);
        }

        V1Rms.capture();
        V2Rms.capture();

        I1Rms.capture();
        I2Rms.capture();
        I3Rms.capture();
        I4Rms.capture();
        I5Rms.capture();
        I6Rms.capture();

        xSemaphoreGive(ready_sem);
    }

    adc_dev->stop();
}
