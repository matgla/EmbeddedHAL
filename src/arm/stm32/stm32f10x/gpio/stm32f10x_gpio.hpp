#pragma once

#include <cstdint>
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

constexpr GPIOSpeed_TypeDef getSpeed(hal::gpio::GpioSpeed speed)
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

constexpr GPIOMode_TypeDef getMode(hal::gpio::GpioMode mode)
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

template <typename T>
class memory_pointer
{
public:
    constexpr memory_pointer(std::intptr_t address)
        : address_(address)
    {
    }

    operator T*() const
    {
        return reinterpret_cast<T*>(address_);
    }

    T* operator->() const
    {
        return operator T*();
    }

private:
    std::intptr_t address_;
};

constexpr static memory_pointer<GPIO_TypeDef> portToRegister(std::uint32_t port)
{
    return memory_pointer<GPIO_TypeDef>(port);
}


template <std::uint32_t port, std::uint32_t pin>
class StmGpio
{
public:
    static void init(const hal::gpio::GpioSpeed speed, const hal::gpio::GpioMode mode)
    {
        initClocks();
        GPIO_InitTypeDef config{pin, getSpeed(speed), getMode(mode)};
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
        if constexpr (port == GPIOA_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        }
        else if (port == GPIOB_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        }
        else if (port == GPIOC_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        }
        else if (port == GPIOD_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
        }
        else if (port == GPIOE_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
        }
        else if (port == GPIOF_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
        }
        else if (port == GPIOF_BASE)
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
        }
        else
        {
            static_assert(true,
                          "Trying to initialize GPIO not supported by STM32F10x architecture");
        }
    }


    constexpr static memory_pointer<GPIO_TypeDef> gpio_ = portToRegister(port);
};

} // namespace gpio
} // namespace stm32f10x
} // namespace hal
