#pragma once

#include <cstdint>

namespace hal
{
namespace time
{

void sleep(uint32_t seconds);
void msleep(uint64_t milliseconds);
void usleep(uint32_t microseconds);

} // namespace time
} // namespace hal