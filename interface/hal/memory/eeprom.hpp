#pragma once

#include <type_traits>

#include <gsl/span>

#include "details/utils.hpp"

namespace hal
{
namespace memory
{

/* addressing 1byte */
class Eeprom
{
public:
    Eeprom();
    void write(std::size_t address, const gsl::span<const uint32_t>& data);
    const gsl::span<const uint8_t> read(uint32_t address, uint32_t size) const;

    template <typename Data>
    void write(std::size_t address, const Data data)
    {
        static_assert(alignof(Data) % 4 == 0, "Data alignment must be divisible by 4");
        static_assert(std::is_pod<Data>::value, "Data must be POD type");
        gsl::span<const uint32_t> buffer{reinterpret_cast<const uint32_t*>(&data), sizeof(Data)};
        write(address, buffer);
    }

    template <typename Data>
    const Data& read(std::size_t address)
    {
        return reinterpret_cast<const Data&>(*read(address, sizeof(Data)).data());
    }


private:
    uint32_t currentAddress_;
};

} // namespace memory
} // namespace hal
