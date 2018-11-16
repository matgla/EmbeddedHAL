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
    { a.init(Speed{}, Output{}) } -> void;
    { a.init(Input{}) } -> void;
    { a.setHigh() } -> void;
    { a.setLow() } -> void;
};
// clang-format on

template <GpioImpl GpioImplType>
class Gpio
{
public:
    constexpr static void init(Speed speed, Output mode)
    {
        GpioImplType::init(speed, mode);
    }

    constexpr static void init(Input mode)
    {
        GpioImplType::init(mode);
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
