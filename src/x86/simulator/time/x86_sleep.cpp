#include "hal/time/sleep.hpp"

#include <thread>

namespace hal
{
namespace time
{

void sleep(std::chrono::seconds seconds)
{
    std::this_thread::sleep_for(seconds);
}

void sleep(std::chrono::microseconds msecs)
{
    std::this_thread::sleep_for(msecs);
}

void sleep(std::chrono::milliseconds msecs)
{
    std::this_thread::sleep_for(msecs);
}


} // namespace time
} // namespace hal
