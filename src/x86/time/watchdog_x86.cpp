#include "hal/time/watchdog.hpp"

#include "details/utils.hpp"

namespace hal
{
namespace time
{

void WatchDog::enable(int milliseconds)
{
    UNUSED(milliseconds);
}

void WatchDog::feed()
{
}

} // namespace time
} // namespace hal
