#ifndef _DAQ_H_
#define _DAQ_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "data_processor.h"

class ADC;

class DAQ
{
public:
    DAQ(ADC* adc);
    ~DAQ();

    void start(void);

private:
    ADC* adc_dev;

    TaskHandle_t task;

    RootMeanSquare V1Rms;

    static void taskEntry(void *arg);

    void mainLoop(void);
};

#endif /* #ifndef _DAQ_H_ */
