#ifndef _DATA_PROCESSOR_H_
#define _DATA_PROCESSOR_H_

class DAQ;

class VirtualSource
{
public:
    virtual float get(void) = 0;
};

class VirtualDataProcessor
{
public:
    virtual void sample(void) = 0;
    virtual void interval(void) = 0;
};

class DataSource : public VirtualSource
{
public:
    DataSource(float * source);

    virtual float get(void);

private:
    float * source_ptr;
};

class RootMeanSquare : public VirtualDataProcessor, public VirtualSource
{
public:
    RootMeanSquare(DAQ * parent, VirtualSource * source);

    virtual void sample(void);
    virtual void interval(void);
    virtual float get(void);

private:
    VirtualSource * sample_source;

    double sos;
    unsigned sample_count;
    float mean_sos;
};

#endif /* #ifndef _DATA_PROCESSOR_H_ */
