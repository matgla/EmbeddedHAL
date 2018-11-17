#pragma once

#include <chrono>

namespace hal
{
namespace time
{

void sleep(std::chrono::seconds seconds);
void sleep(std::chrono::microseconds seconds);
void sleep(std::chrono::milliseconds seconds);

} // namespace time
} // namespace hal