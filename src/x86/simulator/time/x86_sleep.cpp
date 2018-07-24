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

} // namespace time
} // namespace hal
