#pragma once

#include <chrono>

#include "hal/common/timer/ITimer.hpp"

#include <eul/container/observable/observing_list.hpp>
#include <eul/container/observable/observing_node.hpp>
#include <eul/function.hpp>

namespace hal
{
namespace common
{
namespace timer
{

template <typename TimeProviderType>
class Timer : public ITimer
{
public:
    using CallbackType = eul::function<void(), sizeof(std::size_t)>;
    enum class State
    {
        Running,
        Idle
    };

    Timer(const CallbackType& callback, const TimeProviderType& time_provider)
        : time_provider_(time_provider),
          start_time_(0), end_time_(0), callback_(callback), observing_node_(this), state_(State::Idle)
    {
    }

    bool start(const CallbackType& callback, const std::chrono::milliseconds& time)
    {
        if (start(time))
        {
            callback_ = callback;
            return true;
        }
        return false;
    }

    bool start(const std::chrono::milliseconds& time)
    {
        if (state_ == State::Running)
        {
            return false;
        }

        start_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(time_provider_.milliseconds());
        end_time_   = start_time_ + time;
        state_      = State::Running;

        return true;
    }

protected:
    void fire()
    {
        if (state_ == State::Running)
        {
            callback_();
        }
    }

    const TimeProviderType& time_provider_;

    std::chrono::milliseconds start_time_;
    std::chrono::milliseconds end_time_;
    CallbackType callback_;

    eul::container::observing_node<ITimer*> observing_node_;
    State state_;
};

} // namespace timer
} // namespace common
} // namespace hal
