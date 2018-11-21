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
    { a.init(Output{}, Speed{}) } -> void;
    { a.init(Input{}) } -> void;
    { a.setHigh() } -> void;
    { a.setLow() } -> void;
};
// clang-format on

template <GpioImpl GpioImplType>
class Gpio
{
public:
    constexpr static void init(Output mode, Speed speed)
    {
        GpioImplType::init(mode, speed);
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

    using Implementation = GpioImplType;
};

} // namespace gpio
} // namespace hal
