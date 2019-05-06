#pragma once

#include <chrono>
#include <cstdint>

namespace hal
{
namespace time
{

class Time
{
public:
    static void init();
    static void increment_time(const std::chrono::milliseconds& time);
    static std::chrono::milliseconds milliseconds();

private:
    static std::chrono::milliseconds milliseconds_;
};

} // namespace time
} // namespace hal
