#ifndef _DAQ_H_
#define _DAQ_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

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

    static void taskEntry(void *arg);

    void mainLoop(void);
};

#endif /* #ifndef _DAQ_H_ */
