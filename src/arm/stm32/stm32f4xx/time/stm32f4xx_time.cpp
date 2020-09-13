
#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

void Time::init()
{
#ifdef STM32_MICROSECONDS_COUNTER
    initialize_dwt_counter();
#endif
}

std::chrono::milliseconds Time::milliseconds()
{
    return {};//interrupt::get_ticks();
}

std::chrono::microseconds Time::microseconds()
{
    #ifdef STM32_MICROSECONDS_COUNTER
        return std::chrono::microseconds(interrupt::get_ticks().count() * 1000 + (*DWT_CYCCNT / (SystemCoreClock/1000000)));
    #endif
    return std::chrono::microseconds{0};
}

void sleep(std::chrono::microseconds time)
{
    auto previous = Time::microseconds();
    auto counter = previous;
    while (counter < time + previous)
    {
        counter = Time::microseconds();
    }
}

void sleep(std::chrono::milliseconds time)
{
    auto previous = Time::milliseconds();

    auto counter = previous;

    while (counter < time + previous)
    {
        counter = Time::milliseconds();
    }
}

void sleep(std::chrono::seconds time)
{
    sleep(std::chrono::duration_cast<std::chrono::milliseconds>(time));
}

} // namespace time
} // namespace hal




