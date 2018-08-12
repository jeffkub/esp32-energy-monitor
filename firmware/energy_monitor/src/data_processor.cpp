#include "data_processor.h"

#include <cmath>

RootMeanSquare::RootMeanSquare() :
    sos(0.0),
    sample_count(0),
    mean_sos(0.0)
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

void RootMeanSquare::capture(void)
{
    mean_sos = (float) (sos / (double)sample_count);

    sos = 0.0;
    sample_count = 0;
}

float RootMeanSquare::get(void)
{
    return sqrt(mean_sos);
}
