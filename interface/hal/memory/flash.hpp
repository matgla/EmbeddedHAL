#pragma once

#include <cstdint>
#include <gsl/span>

namespace hal
{
namespace memory
{

class Flash
{
public:
    static gsl::span<uint32_t> get_memory(std::size_t address, std::size_t size);

};

} // namespace memory
} // namespace hal
