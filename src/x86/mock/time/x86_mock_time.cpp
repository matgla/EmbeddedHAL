#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

static std::chrono::milliseconds milliseconds_;

void Time::init()
{
}

std::chrono::milliseconds Time::milliseconds()
{
    return milliseconds_;
}

} // namespace time
} // namespace hal
