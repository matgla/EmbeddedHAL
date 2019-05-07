#pragma once

#include <type_traits>
#include <optional>

#include "details/utils.hpp"

namespace hal
{
namespace memory
{

class Eeprom
{
public:
    static void write_u8(std::size_t address, uint8_t value);
    static void write_u16(std::size_t address, uint16_t value);
    static void write_u32(std::size_t address, uint32_t value);

    static std::optional<uint8_t> read_u8(std::size_t address);
    static std::optional<uint16_t> read_u16(std::size_t address);
    static std::optional<uint32_t> read_u32(std::size_t address);
};

} // namespace memory
} // namespace hal
