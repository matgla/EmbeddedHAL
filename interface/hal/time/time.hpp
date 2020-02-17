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

    static void increment_time(const std::chrono::milliseconds& time);
    static void increment_time(int time);
    static std::chrono::milliseconds milliseconds();

    static void add_handler(const eul::function<void(std::chrono::milliseconds), sizeof(void*)>& callback);
};

} // namespace time
} // namespace hal
