// This file is part of embeddedHAL project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once 

#include <cstdint>

namespace hal 
{
namespace core 
{

// Register address offsets for atomic RMW aliases
constexpr uint32_t register_offset_normal_rw_bits = 0x0000;
constexpr uint32_t register_offset_atomic_xor_bits = 0x1000;
constexpr uint32_t register_offset_atomic_set_bits = 0x2000;
constexpr uint32_t register_offset_atomic_clear_bits = 0x3000;

template <typename AddressType, uint32_t operation> 
constexpr void modify_register(AddressType* address, const uint32_t mask)
{
    const uint32_t address_value = reinterpret_cast<std::size_t>(address) + operation;
    *reinterpret_cast<volatile AddressType*>(address_value) = mask; 
}

template <typename AddressType> 
constexpr void register_atomic_set_bits(AddressType* address, const uint32_t mask)
{
    modify_register<AddressType, register_offset_atomic_set_bits>(address, mask);
}

template <typename AddressType>
constexpr void register_atomic_clear_bits(AddressType* address, const uint32_t mask)
{
    modify_register<AddressType, register_offset_atomic_clear_bits>(address, mask);
}

template <typename AddressType>
constexpr void register_atomic_xor_bits(AddressType* address, const uint32_t mask) 
{
    modify_register<AddressType, register_offset_atomic_xor_bits>(address, mask);
}

template <typename AddressType>
constexpr void register_atomic_write_bits(AddressType* address, const uint32_t bits, const uint32_t mask) 
{
    register_atomic_xor_bits(address, (*address ^ bits) & mask);
}

template <typename Register>
class AtomicRegister
{
public:
    AtomicRegister(Register* reg) : reg_(reg)
    {
    }

    void clear_bits(const uint32_t mask) 
    {
        register_atomic_clear_bits(reg_, mask);
    }

    void write_masked(const uint32_t value, const uint32_t mask)
    {
        register_atomic_write_bits(reg_, value, mask);
    }

    void set_bits(const uint32_t mask) 
    {
        register_atomic_set_bits(reg_, mask);
    }
private:
    Register* reg_;
};

} // namespace core
} // namespace hal

