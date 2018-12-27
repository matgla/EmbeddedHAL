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
    void init();

    Time operator++(int);
    Time& operator++();

    Time& operator+=(const std::chrono::milliseconds&);

    std::chrono::milliseconds milliseconds() const;

private:
    std::chrono::milliseconds milliseconds_;
};

} // namespace time
} // namespace hal
