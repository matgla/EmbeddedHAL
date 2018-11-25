#pragma once

#include <stm32f1xx.h>

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

    static void set_core_clock(const uint32_t clock);

    static void set_core_change_callback(const OnCoreClockChangeCallback& callback);
};

} // namespace clock
} // namespace stm32f1xx
} // namespace hal
