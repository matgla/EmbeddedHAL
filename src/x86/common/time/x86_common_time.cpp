#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

std::chrono::milliseconds Time::milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

std::chrono::microseconds Time::microseconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}

} // namespace time
} // namespace hal
