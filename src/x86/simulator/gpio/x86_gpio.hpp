#pragma once

#include <iostream>

namespace hal
{
namespace x86
{
namespace simulator
{
namespace gpio
{

template <std::uint32_t port, std::uint32_t pin>
class X86Gpio
{
public:
    constexpr static void init(hal::gpio::GpioSpeed speed, hal::gpio::GpioMode mode)
    {
        std::cout << "Initialize GPIO: " << port << ":" << pin
                  << ". Speed = " << hal::gpio::to_string(speed)
                  << ", mode = " << hal::gpio::to_string(mode) << std::endl;
    }

    constexpr static void setHigh()
    {
        printHeader() << " -> High" << std::endl;
    }

    constexpr static void setLow()
    {
        printHeader() << " -> Low" << std::endl;
    }

private:
    constexpr static auto& printHeader()
    {
        return (std::cout << "GPIO " << port << ":" << pin);
    }
};

} // namespace gpio
} // namespace simulator
} // namespace x86
} // namespace hal
