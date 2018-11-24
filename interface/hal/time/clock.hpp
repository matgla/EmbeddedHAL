
#pragma once

#include <eul/mpl/tuples/for_each.hpp>

namespace hal
{
namespace time
{

template <typename ClockImplementation, typename... CoreClockChangeSubscribers>
class Clock
{
public:
    Clock(CoreClockChangeSubscribers... subscribers)
        : subscribers_(std::forward<CoreClockChangeSubscribers>(subscribers)...)
    {
    }

    void set_core_clock(const uint32_t clock)
    {
        ClockImplementation::set_core_clock(clock);
        eul::mpl::tuples::for_each(subscribers_, [this](auto& subscriber) {
            subscriber(ClockImplementation::get_core_clock());
        });
    }

    uint32_t get_core_clock() const
    {
        return ClockImplementation::get_core_clock();
    }

private:
    const std::tuple<CoreClockChangeSubscribers...> subscribers_;
};

template <typename... CoreClockChangeSubscribers>
Clock(CoreClockChangeSubscribers...)->Clock<CoreClockChangeSubscribers...>;

} // namespace time
} // namespace hal