#include "hal/time/time.hpp"

#include <cstdint>
#include <cstdio>

#include <vector>

#include <stm32f10x.h>

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
    *SCB_DEMCR |= 0x01000000;
    *DWT_CYCCNT = 0; // reset the counter
    *DWT_CONTROL |= 1 ; // enable the counter
}


void Time::init()
{
    // initialize_dwt_counter();
}

std::chrono::milliseconds Time::milliseconds()
{
    return interrupt::get_ticks();
}

std::chrono::microseconds Time::microseconds()
{
    return 0;
    // return std::chrono::microseconds(interrupt::get_ticks().count() * 1000 + (*DWT_CYCCNT / (SystemCoreClock/1000000)));
}

} // namespace time
} // namespace hal




