#pragma once

#include "hal/common/timer/observed_timer.hpp"

#include "eul/container/observable/observing_list.hpp"

namespace hal
{
namespace common
{
namespace timer
{

class TimerManager
{
public:
    TimerManager();

    void register_timer(ObservedTimer& timer);
    void deregister_timer(ObservedTimer& timer);
    void run();

private:
    eul::container::observing_list<eul::container::observing_node<ObservedTimer*>> timers_;
};

} // namespace timer
} // namespace common
} // namespace hal
