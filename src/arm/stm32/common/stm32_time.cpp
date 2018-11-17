#include "hal/time/time.hpp"

#include <cstdint>

#include <stm32f1xx.h>

namespace hal
{
namespace time
{

volatile uint64_t Time::ticks_(0);

void Time::init()
{
    /* set SysTick to 1ms */
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
}

uint64_t Time::getTicks()
{
    return ticks_;
}

uint64_t Time::milliseconds()
{
    return ticks_;
}

void Time::incrementTicks()
{
    ++ticks_;
}

void Time::setTicks(uint64_t ticks)
{
    ticks_ = ticks;
}

} // namespace time
} // namespace hal


extern "C"
{
    void SysTick_Handler(void);
}

void SysTick_Handler(void)
{
    hal::time::Time::incrementTicks();
}