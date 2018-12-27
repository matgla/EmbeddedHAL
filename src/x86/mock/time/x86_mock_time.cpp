#include "hal/time/time.hpp"

namespace hal
{
namespace time
{

void Time::init()
{
}

Time Time::operator++(int)
{
    Time time(*this);
    ++milliseconds_;
    return time;
}

Time& Time::operator++()
{
    ++milliseconds_;
    return *this;
}

Time& Time::operator+=(const std::chrono::milliseconds& time)
{
    milliseconds_ += time;
    return *this;
}

std::chrono::milliseconds Time::milliseconds() const
{
    return milliseconds_;
}

} // namespace time
} // namespace hal