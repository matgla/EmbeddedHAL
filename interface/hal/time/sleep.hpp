#pragma once

#include <chrono>

namespace hal
{
namespace time
{

void sleep(std::chrono::seconds seconds);
void usleep(uint32_t microseconds);

} // namespace time
} // namespace hal