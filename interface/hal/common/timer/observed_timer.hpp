#pragma once

#include "hal/common/timer/ITimer.hpp"

#include <eul/container/observable/observing_node.hpp>

namespace hal
{
namespace common
{
namespace timer
{

class ObservedTimer : public ITimer
{
public:
    ObservedTimer()
        : observing_node_(this)
    {
    }

    eul::container::observing_node<ObservedTimer*>& observing_node()
    {
        return observing_node_;
    }

protected:
    eul::container::observing_node<ObservedTimer*> observing_node_;
};

} // namespace timer
} // namespace common
} // namespace hal