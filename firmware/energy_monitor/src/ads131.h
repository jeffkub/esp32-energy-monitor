#ifndef _ADS131_H_
#define _ADS131_H_

#include <stdint.h>
#include <stdlib.h>

#include <driver/gpio.h>

class ADS131
{
public:
    ADS131(gpio_num_t cs);

private:
    gpio_num_t cs_pin;

    void regRead(uint16_t addr, void* data, size_t len);
    void regWrite(uint16_t addr, const void* data, size_t len);
};

#endif /* #ifndef _ADS131_H_ */
