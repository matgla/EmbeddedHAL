#pragma once

#include <cstdint>

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace avr
{
namespace gpio
{

template <typename Port, uint32_t pin>
class AvrGpio
{
public:
    constexpr static void init(const hal::gpio::Output mode, const hal::gpio::Speed speed)
    {
        Port::directionRegister() |= (1 << pin);
    }

    constexpr static void setHigh()
    {
        Port::writeRegister() |= (1 << pin);
    }

    constexpr static void setLow()
    {
        Port::writeRegister() &= ~(1 << pin);
    }

    constexpr static void init(const hal::gpio::Input mode)
    {
        Port::directionRegister() &= ~(1 << pin);

        if (mode == hal::gpio::Input::InputFloating)
        {
            Port::writeRegister() &= ~(1 << pin);
        }

        if (mode == hal::gpio::Input::InputPullUpDown)
        {
            Port::writeRegister() |= (1 << pin);
        }
    }

    constexpr static bool read()
    {
        return Port::readRegister() & (1 << pin);
    }
};

} // namespace gpio
} // namespace avr
} // namespae hal
