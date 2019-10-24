#pragma once

#include <stm32f10x.h>

#include <eul/function.hpp>

namespace hal
{
namespace stm32f1xx
{
namespace clock
{

class Clock
{
public:
    using OnCoreClockChangeCallback = eul::function<void(), 2 * sizeof(void*)>;
    static uint32_t get_core_clock();

    // TODO: add clock source
    static void set_core_clock(const uint32_t clock);

    static void set_core_clock_change_callback(const OnCoreClockChangeCallback& callback);

private:
    static OnCoreClockChangeCallback on_core_clock_change_callback_;
};

} // namespace clock
} // namespace stm32f1xx
} // namespace hal
