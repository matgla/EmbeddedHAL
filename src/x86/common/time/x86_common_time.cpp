#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

void Time::init()
{

}

void Time::increment_time(const std::chrono::milliseconds& time)
{

}

std::chrono::milliseconds Time::milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

} // namespace time
} // namespace hal
