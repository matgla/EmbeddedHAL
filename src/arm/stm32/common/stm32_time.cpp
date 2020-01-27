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

std::chrono::milliseconds Time::ticks_{0};
static eul::function<void(std::chrono::milliseconds), sizeof(void*)> callback_;

void Time::init()
{
    ticks_ = std::chrono::seconds(0);
    /* set SysTick to 1ms */
    SysTick_Config(SystemCoreClock / 1000);
}

void Time::increment_time(const std::chrono::milliseconds& time) 
{
    ticks_ += time;
}
static volatile int i = 0;
void Time::increment_time(int time)
{
    ticks_ += std::chrono::milliseconds(time);
}

std::chrono::milliseconds Time::milliseconds()
{
    return ticks_;
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
    hal::time::Time::increment_time(1);
    
    if (hal::time::callback_) 
    {
        hal::time::callback_(hal::time::Time::milliseconds());
    }
}

