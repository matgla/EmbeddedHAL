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
};

} // namespace time
} // namespace hal
