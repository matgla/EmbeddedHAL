#include "hal/time/time.hpp"

#include <cstdint>
#include <cstdio>

#include <vector>

#include <eul/function.hpp>

#include "hal/interrupt/systick.hpp"

namespace hal
{
namespace time
{

volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004;
volatile unsigned int *DWT_CONTROL  = (volatile unsigned int *)0xE0001000;
volatile unsigned int *SCB_DEMCR    = (volatile unsigned int *)0xE000EDFC;

void initialize_dwt_counter(void)
{
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0;
    *DWT_CONTROL = *DWT_CONTROL | 1;
}


void Time::init()
{
#ifdef STM32_MICROSECONDS_COUNTER
    initialize_dwt_counter();
#endif
}

std::chrono::milliseconds Time::milliseconds()
{
    return interrupt::get_ticks();
}

std::chrono::microseconds Time::microseconds()
{
    #ifdef STM32_MICROSECONDS_COUNTER
        return std::chrono::microseconds(interrupt::get_ticks().count() * 1000 + (*DWT_CYCCNT / (SystemCoreClock/1000000)));
    #endif
    return std::chrono::microseconds{0};
}

} // namespace time
} // namespace hal




