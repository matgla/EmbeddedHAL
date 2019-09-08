#pragma once

#include <cstdint>

namespace hal
{
namespace avr
{
namespace gpio
{

struct AvrPortD
{
    static volatile uint8_t& writeRegister();
    static volatile uint8_t& readRegister();
    static volatile uint8_t& directionRegister();
};

} // namespace gpio
} // namespace avr
} // namespace hal
