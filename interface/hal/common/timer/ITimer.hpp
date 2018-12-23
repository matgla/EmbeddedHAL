#pragma once

namespace hal
{
namespace common
{
namespace timer
{

class ITimer
{
public:
    virtual ~ITimer() = default;

    virtual void run() = 0;
};

} // namespace timer
} // namespace common
} // namespace hal
