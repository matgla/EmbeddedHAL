#pragma once

#include "hal/time/timer.hpp"

#include "eul/container/observable/observing_list.hpp"

namespace hal
{
namespace time
{

class TimerManager
{
public:
    TimerManager();

    void register_timer(ITimer* timer);
    void deregister_timer(ITimer* timer);

    void run();

private:
    container::observing_list<observing_node<ITimer*>> timers_;
};

} // namespace time
} // namespace hal
