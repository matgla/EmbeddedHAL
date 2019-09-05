#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace avr
{
namespace gpio
{

struct AvrPortB
{
    static volatile uint8_t& value() { return PORTB; }
};

template <typename Port, uint32_t pin>
class AvrGpio
{
public:
    constexpr static void init(const hal::gpio::Output mode, const hal::gpio::Speed speed)
    {

    }

    static void setHigh()
    {

    }
};

} // namespace gpio
} // namespace avr
} // namespae hal
