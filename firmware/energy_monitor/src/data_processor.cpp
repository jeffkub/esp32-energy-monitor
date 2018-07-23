#include "data_processor.h"

#include <cmath>

RootMeanSquare::RootMeanSquare() :
    sos(0.0),
    sample_count(0),
    rms(0.0f)
{

}

RootMeanSquare::~RootMeanSquare()
{

}

void RootMeanSquare::input(float sample)
{
    sos += (double)sample * (double)sample;
    sample_count++;
}

void RootMeanSquare::calculate(void)
{
    rms = (float) sqrt(sos / (double)sample_count);

    sos = 0.0;
    sample_count = 0;
}

float RootMeanSquare::get(void)
{
    return rms;
}
