#include "hal/time/sleep.hpp"

#include <chrono>

#include <stm32f1xx.h>

#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

volatile uint64_t ticks;

void sleep(std::chrono::seconds seconds)
{
    // msleep(1000 * seconds);
}

void msleep(uint64_t milliseconds)
{
    uint64_t prev = Time::getTicks();
    while (Time::getTicks() < prev + milliseconds)
    {
    }
}

volatile bool initialized               = false;
volatile uint32_t cyclesFor1MicroSecond = 0;

void __attribute__((optimize("O0"))) usleep(uint32_t microseconds)
{
    if (!initialized)
    {
        cyclesFor1MicroSecond = SystemCoreClock / 13000000;
    }
    microseconds = microseconds * cyclesFor1MicroSecond - 10;

    while (microseconds--)
    {
    }
}

} // namespace time
} // namespace hal
