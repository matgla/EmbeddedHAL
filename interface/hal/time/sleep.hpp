#pragma once

#include <chrono>

namespace hal
{
namespace time
{

void sleep(std::chrono::seconds time);
void sleep(std::chrono::microseconds time);
void sleep(std::chrono::milliseconds time);

} // namespace time
} // namespace hal
