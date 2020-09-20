// This file is part of Embedded HAL project.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_usart.hpp"
#include "hal/gpio/digital_input_output_pin.hpp"

#include <eul/utils/unused.hpp>

#include <stm32f10x.h>

#include <unistd.h>

#include <experimental/type_traits>

#include "arm/stm32/stm32f1xx/interfaces/detail/stm32f1xx_usart_traits.hpp"

namespace
{

hal::interfaces::Usart::OnDataCallback* rx_callbacks_[5];
hal::interfaces::Usart::OnSentCallback* tx_callbacks_[5];

const auto empty_rx_callback = [](const uint8_t byte)
{
    UNUSED(byte);
};

const auto empty_tx_callback = []()
{
};


template <int i>
hal::interfaces::Usart::OnDataCallback& get_rx()
{
    return *rx_callbacks_[i];
}

template <int i>
hal::interfaces::Usart::OnSentCallback& get_tx()
{
    return *tx_callbacks_[i];
}

int get_index(uint32_t usart_base)
{
    switch (usart_base)
    {
        case USART1_BASE: return 0;
        case USART2_BASE: return 1;
        case USART3_BASE: return 2;
        case UART4_BASE: return 3;
        case UART5_BASE: return 4;
    }
    return 0;
}

template <uint32_t USART>
struct get_usart_number;

template <>
struct get_usart_number<USART1_BASE>
{
    constexpr static int number = 1;
};

template <>
struct get_usart_number<USART2_BASE>
{
    constexpr static int number = 2;
};

template <>
struct get_usart_number<USART3_BASE>
{
    constexpr static int number = 3;
};

template <>
struct get_usart_number<UART4_BASE>
{
    constexpr static int number = 4;
};

template <>
struct get_usart_number<UART5_BASE>
{
    constexpr static int number = 5;
};

template <uint32_t usart_address>
void handle_usart()
{
    const eul::memory_ptr<USART_TypeDef> usart(usart_address);
    if (usart->SR & USART_SR_RXNE)
    {
        get_rx<get_usart_number<usart_address>::number-1>()(usart->DR);
    }

    if (usart->SR & USART_SR_TXE)
    {
        get_tx<get_usart_number<usart_address>::number-1>()();
    }
}

void init_rcc(uint32_t usart_address)
{
    switch (usart_address)
    {
        case USART1_BASE:
        {
            RCC->APB2ENR = RCC->APB2ENR | hal::interfaces::detail::get_rcc_flag<1>();
            return;
        }
        case USART2_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<2>();
            return;
        }
        case USART3_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<3>();
            return;
        }
        case UART4_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<4>();
            return;
        }
        case UART5_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<5>();
            return;
        }
    }
}

}

extern "C"
{
    void USART1_IRQHandler(void)
    {
        handle_usart<USART1_BASE>();
    }

    void USART2_IRQHandler(void)
    {
        handle_usart<USART2_BASE>();
    }

    void USART3_IRQHandler(void)
    {
        handle_usart<USART3_BASE>();
    }

    void UART4_IRQHandler(void)
    {
        handle_usart<UART4_BASE>();
    }

    void UART5_IRQHandler(void)
    {
        handle_usart<UART5_BASE>();
    }
}

namespace hal
{
namespace interfaces
{
#define impl static_cast<Usart::Impl*>(this)
#define const_impl static_cast<const Usart::Impl*>(this)

void Usart::init(uint32_t baudrate)
{
    impl->init(baudrate);
}

void Usart::set_baudrate(uint32_t baudrate)
{
    impl->set_baudrate(baudrate);
}

void Usart::write(const StreamType& data)
{
    impl->write(data);
}

void Usart::write(const std::string_view& data)
{
    impl->write(data);
}

void Usart::on_data(const OnDataCallback& callback)
{
    impl->on_data(callback);
}

void Usart::on_sent(const OnSentCallback& callback)
{
    impl->on_sent(callback);
}

const IRQn get_irqn(uint32_t usart_base)
{
    switch (usart_base)
    {
        case USART1_BASE: return detail::get_irq_v<IRQn, 1>;
        case USART2_BASE: return detail::get_irq_v<IRQn, 2>;
        case USART3_BASE: return detail::get_irq_v<IRQn, 3>;
        case UART4_BASE: return detail::get_irq_v<IRQn, 4>;
        case UART5_BASE: return detail::get_irq_v<IRQn, 5>;
    }

    return detail::get_irq_v<IRQn, -1>;
}

Usart::Impl::Impl(hal::gpio::DigitalInputOutputPin& rx, hal::gpio::DigitalInputOutputPin& tx, uint32_t usart_address)
    : usart_(usart_address)
    , rx_(rx)
    , tx_(tx)
    , rx_callback_(empty_rx_callback)
    , tx_callback_(empty_tx_callback)
{
    rx_callbacks_[get_index(usart_address)] = &rx_callback_;
    tx_callbacks_[get_index(usart_address)] = &tx_callback_;
}

void Usart::Impl::init(const uint32_t baudrate)
{
    init(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
}

void Usart::Impl::set_baudrate(const uint32_t baudrate)
{
    set_baudrate(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
}

void Usart::Impl::write(const gsl::span<const uint8_t>& data)
{
    for (const auto byte : data)
    {
        write(byte);
    }
}

void Usart::Impl::write(const std::string_view& data)
{
    for (const auto byte : data)
    {
        write(byte);
    }
}

void Usart::Impl::on_data(const OnDataCallback& callback)
{
    rx_callback_ = callback;
}

void Usart::Impl::on_sent(const OnSentCallback& callback)
{
    tx_callback_ = callback;
}

void Usart::Impl::write(const char byte)
{
    wait_for_tx();
    usart_->DR = byte;
}

void Usart::Impl::set_baudrate(const uint32_t bus_frequency, const uint32_t baudrate)
{
    usart_->BRR = bus_frequency / baudrate;
}

void Usart::Impl::init(const uint32_t bus_frequency, const uint32_t baudrate)
{
    static_cast<hal::gpio::DigitalInputOutputPin::Impl*>(&tx_)->init(
        hal::gpio::Output::OutputPushPull,
        hal::gpio::Speed::Medium,
        hal::gpio::Function::Alternate);

    rx_.init(hal::gpio::Input::InputFloating);
    init_rcc(usart_.address());

    set_baudrate(bus_frequency, baudrate);

    usart_->CR1 = usart_->CR1 | USART_CR1_TE;
    /* enable rx */
    usart_->CR1 = usart_->CR1 | USART_CR1_RE;
    /* enable USART */
    usart_->CR1 = usart_->CR1 | USART_CR1_UE;
    /* enable Rx intterupt */
    usart_->CR1 = usart_->CR1 | USART_CR1_RXNEIE;

    NVIC_EnableIRQ(get_irqn(usart_.address()));
}

void Usart::Impl::wait_for_tx()
{
    while (!(usart_->SR & USART_SR_TXE))
    {
    }
}

} // namespace interfaces
} // namespace hal
