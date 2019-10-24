#include "hal/time/sleep.hpp"
#include "hal/time/time.hpp"

#include <stm32f10x.h>

namespace hal
{
namespace time
{

/* This is really bad implementation for usleep, but without timer hard to do this better */
void __attribute__((optimize("O0"))) sleep(std::chrono::microseconds time)
{
    const uint32_t numberOfCyclesForOneMicrosecond = SystemCoreClock / 1000000 / 4;

    uint32_t t = time.count() * numberOfCyclesForOneMicrosecond;
    while (t--)
    {
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


    // while (counter < time.count())
    // {
    //     const auto current = Time::getTicks();
    //     if (previous < current)
    //     {
    //         counter += current - previous;
    //         previous = current;
    //     }
    //     else if (previous > current)
    //     {
    //         counter += previous + current;
    //         previous = current;
    //     }
    // }
}

void sleep(std::chrono::seconds time)
{
    sleep(std::chrono::duration_cast<std::chrono::milliseconds>(time));
}

} // namespace time
} // namespace hal
