#pragma once

#include "arm/stm32/stm32f1xx/clock/stm32f1xx_clock.hpp"
#include "hal/clock/clock.hpp"

namespace hal
{
namespace clock
{

template <typename... Subscribers>
using Clock = hal::clock::ClockBase<hal::stm32f1xx::clock::Clock, Subscribers...>;

} // namespace clock
} // namespace hal