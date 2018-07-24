#pragma once

#include <chrono>

namespace hal
{
namespace time
{

void sleep(std::chrono::seconds seconds);

} // namespace time
} // namespace hal