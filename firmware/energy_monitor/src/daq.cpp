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

void DAQ::mainLoop(void)
{
    adc_dev->start();

    while(true)
    {

    }

    adc_dev->stop();
}
