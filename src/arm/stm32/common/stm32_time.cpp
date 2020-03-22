#include "hal/time/time.hpp"

#include <cstdint>
#include <cstdio>

#include <vector>


#include <eul/function.hpp>

#include "hal/interrupt/systick.hpp"

namespace hal
{
namespace time
{

void Time::init()
{
    interrupt::set_systick_period(std::chrono::milliseconds(1));
}

std::chrono::milliseconds Time::milliseconds()
{
    return interrupt::get_ticks();
}

} // namespace time
} // namespace hal




