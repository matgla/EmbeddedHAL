
#pragma once

#include <eul/mpl/tuples/for_each.hpp>

namespace hal
{
namespace clock
{

template <typename ClockImplementation, typename... CoreClockChangeSubscribers>
class ClockBase
{
public:
    using SelfType = ClockBase<ClockImplementation, CoreClockChangeSubscribers...>;
    ClockBase(CoreClockChangeSubscribers... subscribers)
        : subscribers_(std::forward<CoreClockChangeSubscribers>(subscribers)...)
    {
        ClockImplementation::set_core_clock_change_callback([this]() { on_clock_change(); });
    }

    void set_core_clock(const uint32_t clock)
    {
        ClockImplementation::set_core_clock(clock);
    }

    uint32_t get_core_clock() const
    {
        return ClockImplementation::get_core_clock();
    }

private:
    void on_clock_change()
    {
        eul::mpl::tuples::for_each(subscribers_, [this](auto& subscriber) {
            subscriber(ClockImplementation::get_core_clock());
        });
    }
    const std::tuple<CoreClockChangeSubscribers...> subscribers_;
};

template <typename Impl, typename... CoreClockChangeSubscribers>
ClockBase(CoreClockChangeSubscribers...)->ClockBase<Impl, CoreClockChangeSubscribers...>;

} // namespace clock
} // namespace hal
