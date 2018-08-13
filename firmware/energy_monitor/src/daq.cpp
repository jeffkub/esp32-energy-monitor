#include "daq.h"

#include <cassert>

#include "ads131.h"

#define VSENSE_SCALE        ((float)(1.0 / (4.7e3 / (600e3 + 4.7e3) / 2.0 * 0.5)))
/* 200A:26.6mA CT sensor */
#define ISENSE_MAINS_SCALE  ((float)(1.0 / ((0.0266 / 200.0) * 22.0 / 2.0 * 0.5)))
/* 100A:50mA CT sensor */
#define ISENSE_AUX_SCALE    ((float)(1.0 / ((0.050 / 100.0) * 22.0 / 2.0 * 0.5)))

DAQ::DAQ(ADC* adc, unsigned interval) :
    adc_dev(adc),
    interval_len(interval),
    V1Sample(&sample_data[7], VSENSE_SCALE),
    V2Sample(&sample_data[6], VSENSE_SCALE),
    I1Sample(&sample_data[5], ISENSE_MAINS_SCALE),
    I2Sample(&sample_data[4], ISENSE_MAINS_SCALE),
    I3Sample(&sample_data[3], ISENSE_AUX_SCALE),
    I4Sample(&sample_data[2], ISENSE_AUX_SCALE),
    I5Sample(&sample_data[1], ISENSE_AUX_SCALE),
    I6Sample(&sample_data[0], ISENSE_AUX_SCALE),
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
