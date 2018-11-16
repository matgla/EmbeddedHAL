#pragma once

#include <cstdint>
#include <cstdio>

#include <stm32f1xx.h>

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace stm32f10x
{
namespace gpio
{

enum class Port
{
    A,
    B,
    C,
    D
};

constexpr uint32_t getPort(const Port port)
{
    switch (port)
    {
        case Port::A:
            return GPIOA_BASE;
        case Port::B:
            return GPIOB_BASE;
        case Port::C:
            return GPIOC_BASE;
        case Port::D:
            return GPIOD_BASE;
    }
}

// constexpr GPIOSpeed_TypeDef getSpeed(hal::gpio::GpioSpeed speed)
// {
//     switch (speed)
//     {
//         case hal::gpio::GpioSpeed::Low:
//             return GPIO_Speed_2MHz;
//         case hal::gpio::GpioSpeed::Medium:
//             return GPIO_Speed_10MHz;
//         case hal::gpio::GpioSpeed::High:
//             return GPIO_Speed_50MHz;
//     }
// }

// constexpr GPIOMode_TypeDef getMode(hal::gpio::GpioMode mode)
// {
//     switch (mode)
//     {
//         case hal::gpio::GpioMode::Analog:
//             return GPIO_Mode_AIN;
//         case hal::gpio::GpioMode::InputFloating:
//             return GPIO_Mode_IN_FLOATING;
//         case hal::gpio::GpioMode::InputPullDown:
//             return GPIO_Mode_IPD;
//         case hal::gpio::GpioMode::InputPullUp:
//             return GPIO_Mode_IPU;
//         case hal::gpio::GpioMode::OutputOpenDrain:
//             return GPIO_Mode_Out_OD;
//         case hal::gpio::GpioMode::OutputPushPull:
//             return GPIO_Mode_Out_PP;
//     }
// }

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

enum class Output : uint8_t
{
    PushPull  = 0x0,
    OpenDrain = 0x1
};

enum class Speed : uint8_t
{
    Low    = 0x1,
    Medium = 0x2,
    High   = 0x3
};

constexpr uint8_t get_pin_mask(uint8_t o, uint8_t s)
{
    return (o << 2) | s;
}

constexpr uint32_t set_pin_mask(uint32_t reg, uint32_t pin, uint8_t mask)
{
    reg &= ~(0xF << pin * 4);       // reset pin state
    return reg | (mask << pin * 4); // set pin state
}

constexpr uint32_t get_port_state(uint32_t reg, uint32_t pin, uint8_t o, uint8_t s)
{
    return set_pin_mask(reg, pin, get_pin_mask(o, s));
}

constexpr uint8_t get_mode_mask(hal::gpio::GpioMode m)
{
    switch (m)
    {
        case hal::gpio::GpioMode::OutputPushPull:
            return 0x0;
        case hal::gpio::GpioMode::OutputOpenDrain:
            return 0x1;
    }
}

constexpr uint8_t get_speed_mask(hal::gpio::GpioSpeed s)
{
    switch (s)
    {
        case hal::gpio::GpioSpeed::Low:
            return 0x1;
        case hal::gpio::GpioSpeed::Medium:
            return 0x2;
        case hal::gpio::GpioSpeed::High:
            return 0x3;
    }
}

template <Port port, std::uint32_t pin>
class StmGpio
{
public:
    static void init(const hal::gpio::GpioSpeed speed, const hal::gpio::GpioMode mode)
    {
        initClocks();

        // set as output
        if constexpr (pin <= 7)
        {
            port_->CRL = get_port_state(port_->CRL, pin, get_mode_mask(mode), get_speed_mask(speed));
        }
        // GPIO_InitTypeDef config{pin, getSpeed(speed), getMode(mode)};
        // GPIO_Init(gpio_, &config);
    }

    constexpr static volatile void setHigh()
    {
        port_->BSRR |= 1 << pin;
    }

    constexpr static volatile void setLow()
    {
        port_->BRR |= 1 << pin;
    }

private:
    constexpr static void initClocks()
    {
        if constexpr (port == Port::A)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        else if (port == Port::B)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        else if (port == Port::C)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        else if (port == Port::D)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        else
        {
            static_assert(true,
                          "Trying to initialize GPIO not supported by STM32F10x architecture");
        }
    }


    constexpr static memory_pointer<GPIO_TypeDef> port_ = getPort(port);
};

} // namespace gpio
} // namespace stm32f10x
} // namespace hal
