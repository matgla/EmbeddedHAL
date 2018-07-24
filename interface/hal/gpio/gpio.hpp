#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

// clang-format off
template <typename T>
concept bool GpioImpl = requires(T a) 
{
    { a.init(GpioSpeed{}, GpioMode{}) } -> void;
    { a.setHigh() } -> void;
    { a.setLow() } -> void;
};
// clang-format on

template <GpioImpl GpioImplType>
class Gpio
{
public:
    constexpr static void init(GpioSpeed speed, GpioMode mode)
    {
        GpioImplType::init(speed, mode);
    }

    constexpr static void setHigh()
    {
        GpioImplType::setHigh();
    }

    constexpr static void setLow()
    {
        GpioImplType::setLow();
    }
};

} // namespace gpio
} // namespace hal
