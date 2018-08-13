#include "data_processor.h"

#include <cmath>

#include "daq.h"

/* DataSource class */
DataSource::DataSource(float * source) :
    source_ptr(source)
{

}

float DataSource::get(void)
{
    return *source_ptr;
}

/* RootMeanSquare class */
RootMeanSquare::RootMeanSquare(DAQ * parent, VirtualSource * source) :
    sample_source(source),
    sos(0.0),
    sample_count(0),
    mean_sos(0.0)
{
    parent->addDataProcessor(this);
}

void RootMeanSquare::sample(void)
{
    double sample_val = (double)sample_source->get();
    sos += (double)sample_val * (double)sample_val;
    sample_count++;
}

void RootMeanSquare::interval(void)
{
    mean_sos = (float) (sos / (double)sample_count);

    sos = 0.0;
    sample_count = 0;
}

float RootMeanSquare::get(void)
{
    return sqrt(mean_sos);
}
