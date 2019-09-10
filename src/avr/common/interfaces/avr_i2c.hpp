#pragma once

#include <cstdint>
#include <gsl/span>

namespace hal
{
namespace avr
{
namespace common
{
namespace interfaces
{

class AvrI2C
{
public:
    static void init();
    static bool start(uint8_t address);
    static void stop();
    static bool write(uint8_t byte);
    static void write(gsl::span<uint8_t>& data);

private:
    inline static uint32_t twi_register_status = 0;
};

} // namespace interfaces
} // namespace common
} // namespace avr
} // namespace hal
