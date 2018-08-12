#ifndef _DATA_PROCESSOR_H_
#define _DATA_PROCESSOR_H_

class RootMeanSquare
{
public:
    RootMeanSquare();
    ~RootMeanSquare();

    void input(float sample);
    void capture(void);
    float get(void);

private:
    double sos;
    unsigned sample_count;
    float mean_sos;
};

#endif /* #ifndef _DATA_PROCESSOR_H_ */
