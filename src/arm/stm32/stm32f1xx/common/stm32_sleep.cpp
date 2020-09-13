#include "hal/time/sleep.hpp"
#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

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
