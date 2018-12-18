#pragma once

#include "hal/time/timer.hpp"


namespace hal
{
namespace time
{

template <typename CallbackType, typename Time>
class TimeoutTimer : public Timer
{
public:
    void run() override
    {
    }
};

} // namespace time
} // namespace hal
