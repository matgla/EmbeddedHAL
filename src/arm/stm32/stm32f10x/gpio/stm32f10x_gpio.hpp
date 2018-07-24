#pragma once

#include <cstdio>

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace stm32f10x
{
namespace gpio
{

constexpr uint32_t getSpeed(hal::gpio::GpioSpeed speed)
{
    switch (speed)
    {
        case hal::gpio::GpioSpeed::Low:
            return GPIO_Speed_2MHz;
        case hal::gpio::GpioSpeed::Medium:
            return GPIO_Speed_10MHz;
        case hal::gpio::GpioSpeed::High:
            return GPIO_Speed_50MHz;
    }
}

constexpr uint32_t getMode(hal::gpio::GpioMode mode)
{
    switch (mode)
    {
        case hal::gpio::GpioMode::Analog:
            return GPIO_Mode_AIN;
        case hal::gpio::GpioMode::InputFloating:
            return GPIO_Mode_IN_FLOATING;
        case hal::gpio::GpioMode::InputPullDown:
            return GPIO_Mode_IPD;
        case hal::gpio::GpioMode::InputPullUp:
            return GPIO_Mode_IPU;
        case hal::gpio::GpioMode::OutputOpenDrain:
            return GPIO_Mode_Out_OD;
        case hal::gpio::GpioMode::OutputPushPull:
            return GPIO_Mode_Out_PP;
    }
}

template <std::uint32_t port, std::uint32_t pin>
class StmGpio
{
public:
    constexpr static void init(hal::gpio::GpioSpeed speed, hal::gpio::GpioMode mode)
    {
        initClocks();
        GPIO_InitTypeDef config;
        config.GPIO_Pin   = pin;
        config.GPIO_Speed = getSpeed(speed);
        config.GPIO_Mode  = getMode(mode);
        GPIO_Init(gpio_, &config);
    }

    constexpr static void setHigh()
    {
        GPIO_SetBits(gpio_, pin);
    }

    constexpr static void setLow()
    {
        GPIO_ResetBits(gpio_, pin);
    }

private:
    constexpr static void initClocks()
    {
        if constexpr (gpio_ == GPIOA)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        }
        else if (gpio_ == GPIOB)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        }
        else if (gpio_ == GPIOC)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        }
        else if (gpio_ == GPIOD)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        }
        else if (gpio_ == GPIOE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
        }
        else if (gpio_ == GPIOF)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
        }
        else if (gpio_ == GPIOG)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
        }
        else
        {
            static_assert(true,
                          "Trying to initialize GPIO not supported by STM32F10x architecture");
        }
    }

    constexpr static GPIO_TypeDef* getRegister()
    {
        return reinterpret_cast<GPIO_TypeDef*>(port);
    }

    constexpr static bool GPIO_TypeDef* gpio_ = getRegister();
};

} // namespace gpio
} // namespace stm32f10x
} // namespace hal
