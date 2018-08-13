#include "daq.h"

#include <cassert>

#include "ads131.h"

DAQ::DAQ(ADC* adc, unsigned interval) :
    adc_dev(adc),
    interval_len(interval),
    V1Sample(&sample_data[7]),
    V2Sample(&sample_data[6]),
    I1Sample(&sample_data[5]),
    I2Sample(&sample_data[4]),
    I3Sample(&sample_data[3]),
    I4Sample(&sample_data[2]),
    I5Sample(&sample_data[1]),
    I6Sample(&sample_data[0]),
    V1Rms(this, &V1Sample),
    V2Rms(this, &V2Sample),
    I1Rms(this, &I1Sample),
    I2Rms(this, &I2Sample),
    I3Rms(this, &I3Sample),
    I4Rms(this, &I4Sample),
    I5Rms(this, &I5Sample),
    I6Rms(this, &I6Sample)
{
    ready_sem = xSemaphoreCreateBinary();
    assert(ready_sem != NULL);
}

DAQ::~DAQ()
{
    vSemaphoreDelete(ready_sem);
}

void DAQ::addDataProcessor(VirtualDataProcessor* dataProcessor)
{
    dataProcessors.push_back(dataProcessor);
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
    adc_dev->start();

    while(true)
    {
        for(unsigned sample = 0; sample < interval_len; sample++)
        {
            adc_dev->read(sample_data, CHANNEL_COUNT);

            for(std::vector<VirtualDataProcessor *>::iterator it = dataProcessors.begin(); it != dataProcessors.end(); it++)
            {
                (*it)->sample();
            }
        }

        for(std::vector<VirtualDataProcessor *>::iterator it = dataProcessors.begin(); it != dataProcessors.end(); it++)
        {
            (*it)->interval();
        }

        xSemaphoreGive(ready_sem);
    }

    adc_dev->stop();
}
