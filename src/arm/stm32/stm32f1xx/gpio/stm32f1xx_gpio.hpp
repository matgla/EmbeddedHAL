#pragma once

#include <cstdint>
#include <cstdio>

#include <stm32f10x.h>

#include <eul/memory_ptr.hpp>

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace stm32f1xx
{
namespace gpio
{

namespace detail
{

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

constexpr uint8_t get_mode_mask(hal::gpio::Input m)
{
    switch (m)
    {
        case hal::gpio::Input::Analog:
            return 0x00;
        case hal::gpio::Input::InputFloating:
            return 0x01;
        case hal::gpio::Input::InputPullUpDown:
            return 0x02;
    }
    return 0x0;
}

constexpr uint8_t get_mode_mask(hal::gpio::Output m)
{
    switch (m)
    {
        case hal::gpio::Output::OutputPushPull:
            return 0x0;
        case hal::gpio::Output::OutputOpenDrain:
            return 0x1;
    }
    return 0x0;
}

constexpr uint8_t get_alternate_mode_mask(hal::gpio::Output m)
{
    switch (m)
    {
        case hal::gpio::Output::OutputPushPull:
            return 0x2;
        case hal::gpio::Output::OutputOpenDrain:
            return 0x3;
    }
    return 0x0;
}

constexpr uint8_t get_speed_mask(hal::gpio::Speed s)
{
    switch (s)
    {
        case hal::gpio::Speed::Default:
        case hal::gpio::Speed::Low:
            return 0x1;
        case hal::gpio::Speed::Medium:
            return 0x2;
        case hal::gpio::Speed::High:
            return 0x3;
    }
    return 0x0;
}

} // namespace detail

enum class Function
{
    Standard,
    Alternate
};

class Stm32GpioCommon
{
public:
    constexpr Stm32GpioCommon(uint32_t port, uint32_t pin, uint32_t rcc_mask)
        : port_(port)
        , pin_(pin)
        , rcc_mask_(rcc_mask)
    {
    }

    void init(const hal::gpio::Output mode, const hal::gpio::Speed speed)
    {
        initClocks();

        configurePort(detail::get_mode_mask(mode), detail::get_speed_mask(speed));
    }

    void init(const hal::gpio::Output mode, const hal::gpio::Speed speed, Function function)
    {
        if (function == Function::Standard)
        {
            init(mode, speed);
        }
        else if (function == Function::Alternate)
        {
            initClocks();
            configurePort(detail::get_alternate_mode_mask(mode), detail::get_speed_mask(speed));
        }
    }

    void init(const hal::gpio::Input mode)
    {
        initClocks();

        configurePort(detail::get_mode_mask(mode), 0x0);
        port_->BSRR = port_->BSRR | (1 << pin_);
    }

    void setHigh()
    {
        port_->BSRR = port_->BSRR | (1 << pin_);
    }

    void setLow()
    {
        port_->BRR = port_->BRR | (1 << pin_);
    }

    bool read()
    {
        return (port_->IDR & (1 << pin_)) !=0;
    }

private:
    void configurePort(uint8_t mode, uint8_t speed)
    {
        if (pin_ <= 7)
        {
            port_->CRL = detail::get_port_state(port_->CRL, pin_, mode, speed);
        }
        else
        {
            port_->CRH = detail::get_port_state(port_->CRH, pin_ - 8, mode, speed);
        }
    }

    void initClocks()
    {
        RCC->APB2ENR = RCC->APB2ENR | rcc_mask_;
    }

    volatile eul::memory_ptr<GPIO_TypeDef> port_;
    const uint32_t pin_;
    const uint32_t rcc_mask_;
};

template <uint32_t port, uint32_t pin, uint32_t rcc_mask>
class StmGpio : public Stm32GpioCommon
{
public:
    StmGpio() : Stm32GpioCommon(port, pin, rcc_mask)
    {
    }

    static Stm32GpioCommon& get()
    {
        static Stm32GpioCommon c(port, pin, rcc_mask);
        return c;
    }
};

} // namespace gpio
} // namespace stm32f1xx
} // namespace hal
