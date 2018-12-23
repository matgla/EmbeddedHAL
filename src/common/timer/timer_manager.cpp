#include "hal/common/timer/timer_manager.hpp"

namespace hal
{
namespace common
{
namespace timer
{

TimerManager::TimerManager()
{
}

void TimerManager::register_timer(ObservedTimer& timer)
{
    timers_.push_back(timer.observing_node());
}

void TimerManager::deregister_timer(ObservedTimer& timer)
{
    timer.observing_node().reset();
}

void TimerManager::run()
{
    for (auto& timer : timers_)
    {
        timer.data()->run();
    }
}

} // namespace timer
} // namespace common
} // namespace hal