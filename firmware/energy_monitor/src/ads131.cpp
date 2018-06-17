#include "ads131.h"

ADS131::ADS131(gpio_num_t cs) :
    cs_pin(cs)
{
    return;
}

void ADS131::regRead(uint16_t addr, void* data, size_t len)
{
    return;
}

void ADS131::regWrite(uint16_t addr, const void* data, size_t len)
{
    return;
}
