#pragma once

#include <chrono>
#include <cstdint>

#include <eul/function.hpp>

namespace hal
{
namespace time
{

class Time
{
public:
    static void init();

    static std::chrono::milliseconds milliseconds();
    static std::chrono::microseconds microseconds();
};

} // namespace time
} // namespace hal
