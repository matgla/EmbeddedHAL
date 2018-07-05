#include <stm32f10x_gpio.h>

#include "hal/gpio/digitalOut.hpp"

namespace hal
{
namespace gpio
{

template <Port port>
constexpr DigitalOut<port>::DigitalOut(const Pin pin)
    : pin_(pin)
{
}

template <Port port>
constexpr void DigitalOut<port>::high() const
{
    ConvertPort<port>::to_stm32()->BSRR = pin_;
}

template <Port port>
constexpr void DigitalOut<port>::low() const
{
    ConvertPort<port>::to_stm32()->BSRR = pin_;
}

} // namespace gpio
} // namespace hal
