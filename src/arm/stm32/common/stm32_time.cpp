#include "hal/time/time.hpp"

#include <cstdint>
#include <cstdio>

#include <vector>

#include <stm32f10x.h>

#include <eul/function.hpp>

namespace hal
{
namespace time
{

uint32_t ticks_{0};
static eul::function<void(std::chrono::milliseconds), sizeof(void*)> callback_;

void Time::init()
{
    ticks_ = 0;
    /* set SysTick to 1ms */
    SysTick_Config(SystemCoreClock / 10);
}

void Time::increment_time(const std::chrono::milliseconds& time)
{
    ticks_ += time.count();
}

void Time::increment_time(int time)
{
    ticks_ += time;
}

std::chrono::milliseconds Time::milliseconds()
{
    uint32_t ticks = ticks_;
    return std::chrono::milliseconds(ticks);
}

void Time::add_handler(const eul::function<void(std::chrono::milliseconds), sizeof(void*)>& callback)
{
    callback_ = callback;
}

} // namespace time
} // namespace hal


extern "C"
{
    void SysTick_Handler(void);
}

void SysTick_Handler(void)
{
    hal::time::ticks_ += 100;
    if (hal::time::callback_)
    {
        hal::time::callback_(hal::time::Time::milliseconds());
    }
}

