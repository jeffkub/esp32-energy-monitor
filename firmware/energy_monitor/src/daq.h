#ifndef _DAQ_H_
#define _DAQ_H_

#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include "data_processor.h"

#define CHANNEL_COUNT   8

class ADC;

class DAQ
{
public:
    DAQ(ADC* adc, unsigned interval);
    ~DAQ();

    void addDataProcessor(VirtualDataProcessor* dataProcessor);

    void start(void);

    void wait(void);

    inline float getV1(void) { return V1Rms.get(); }
    inline float getV2(void) { return V2Rms.get(); }

    inline float getI1(void) { return I1Rms.get(); }
    inline float getI2(void) { return I2Rms.get(); }
    inline float getI3(void) { return I3Rms.get(); }
    inline float getI4(void) { return I4Rms.get(); }
    inline float getI5(void) { return I5Rms.get(); }
    inline float getI6(void) { return I6Rms.get(); }

private:
    ADC* adc_dev;
    unsigned interval_len;

    SemaphoreHandle_t ready_sem;

    TaskHandle_t task;

    float sample_data[CHANNEL_COUNT];
    std::vector<VirtualDataProcessor *> dataProcessors;

    DataSource V1Sample;
    DataSource V2Sample;

    DataSource I1Sample;
    DataSource I2Sample;
    DataSource I3Sample;
    DataSource I4Sample;
    DataSource I5Sample;
    DataSource I6Sample;

    RootMeanSquare V1Rms;
    RootMeanSquare V2Rms;

    RootMeanSquare I1Rms;
    RootMeanSquare I2Rms;
    RootMeanSquare I3Rms;
    RootMeanSquare I4Rms;
    RootMeanSquare I5Rms;
    RootMeanSquare I6Rms;

    static void taskEntry(void *arg);

    void mainLoop(void);
};

#endif /* #ifndef _DAQ_H_ */
