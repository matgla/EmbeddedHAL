#pragma once

#include <cstdint>
#include <span>

namespace hal
{
namespace memory
{

class Flash
{
public:
    static std::span<uint32_t> get_memory(std::size_t address, std::size_t size);

    bool erase(std::size_t address, std::size_t size);
    bool write(std::size_t address, std::span<const uint8_t> data);
};

} // namespace memory
} // namespace hal
