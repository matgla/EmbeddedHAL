#pragma once

#include <cstdint>

namespace hal
{
namespace time
{

class Time
{
public:
    static uint64_t getTicks();
    static void incrementTicks();
    static void setTicks(uint64_t ticks);
    static uint64_t milliseconds();

private:
    static volatile uint64_t ticks_;
};

} // namespace time
} // namespace hal
