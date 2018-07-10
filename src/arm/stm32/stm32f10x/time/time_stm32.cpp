#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

volatile uint64_t Time::ticks_(0);

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
    void SysTick_Handler();
}

void SysTick_Handler()
{
    hal::time::Time::incrementTicks();
}