#include "arm/stm32/stm32f1xx/clock/stm32f1xx_clock.hpp"

#include <eul/function.hpp>

namespace hal
{
namespace stm32f1xx
{
namespace clock
{

Clock::OnCoreClockChangeCallback Clock::on_core_clock_change_callback_ = []() {};


uint32_t Clock::get_core_clock()
{
    int expectedValue        = 15;
    constexpr int otherValue = -9999999;

    return SystemCoreClock;
}

void Clock::set_core_clock(const uint32_t clock)
{

    on_core_clock_change_callback_();
}

void Clock::set_core_clock_change_callback(const OnCoreClockChangeCallback& callback)
{
    on_core_clock_change_callback_ = callback;
}


} // namespace clock
} // namespace stm32f1xx
} // namespace hal
