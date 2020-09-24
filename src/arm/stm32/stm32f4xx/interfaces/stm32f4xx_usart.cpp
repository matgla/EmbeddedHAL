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


#include <eul/utils/unused.hpp>
#include "arm/stm32/stm32f4xx/interfaces/stm32f4xx_usart.hpp"
#include "hal/gpio/digital_input_output_pin.hpp"


#include <stm32f4xx.h>
#include <stm32f4xx_hal_gpio_ex.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_usart.h>
#include <stm32f4xx_hal_uart.h>

#include <unistd.h>

#include <experimental/type_traits>

#include "arm/stm32/stm32f4xx/interfaces/detail/stm32f4xx_usart_traits.hpp"

namespace
{

hal::interfaces::Usart::OnDataCallback* rx_callbacks_[10];
hal::interfaces::Usart::OnSentCallback* tx_callbacks_[10];

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
        #ifdef USART1_BASE
        case USART1_BASE: return 0;
        #endif
        #ifdef USART2_BASE
        case USART2_BASE: return 1;
        #endif
        #ifdef USART3_BASE
        case USART3_BASE: return 2;
        #endif
        #ifdef UART4_BASE
        case UART4_BASE: return 3;
        #endif
        #ifdef UART5_BASE
        case UART5_BASE: return 4;
        #endif
        #ifdef USART6_BASE
        case USART6_BASE: return 5;
        #endif
        #ifdef UART7_BASE
        case UART7_BASE: return 6;
        #endif
        #ifdef UART8_BASE
        case UART8_BASE: return 7;
        #endif
        #ifdef UART9_BASE
        case UART8_BASE: return 8;
        #endif
        #ifdef UART10_BASE
        case UART8_BASE: return 9;
        #endif
    }
    return 0;
}

template <uint32_t USART>
struct get_usart_number;

#ifdef USART1_BASE
template <>
struct get_usart_number<USART1_BASE>
{
    constexpr static int number = 1;
};
#endif
#ifdef USART2_BASE
template <>
struct get_usart_number<USART2_BASE>
{
    constexpr static int number = 2;
};
#endif
#ifdef USART3_BASE
template <>
struct get_usart_number<USART3_BASE>
{
    constexpr static int number = 3;
};
#endif
#ifdef UART4_BASE
template <>
struct get_usart_number<UART4_BASE>
{
    constexpr static int number = 4;
};
#endif
#ifdef UART5_BASE
template <>
struct get_usart_number<UART5_BASE>
{
    constexpr static int number = 5;
};
#endif
#ifdef USART6_BASE
template <>
struct get_usart_number<USART6_BASE>
{
    constexpr static int number = 6;
};
#endif
#ifdef UART7_BASE
template <>
struct get_usart_number<UART7_BASE>
{
    constexpr static int number = 7;
};
#endif
#ifdef UART8_BASE
template <>
struct get_usart_number<UART8_BASE>
{
    constexpr static int number = 8;
};
#endif
#ifdef UART9_BASE
template <>
struct get_usart_number<UART9_BASE>
{
    constexpr static int number = 9;
};
#endif
#ifdef UART10_BASE
template <>
struct get_usart_number<UART10_BASE>
{
    constexpr static int number = 10;
};
#endif

template <uint32_t usart_address>
void handle_usart()
{
    eul::memory_ptr<USART_TypeDef> usart(usart_address);
    if (usart->SR & USART_SR_RXNE)
    {
        get_rx<get_usart_number<usart_address>::number-1>()(usart->DR);
        usart->SR = ~(USART_SR_RXNE);
    }

    if (usart->SR & USART_SR_TXE)
    {
        get_tx<get_usart_number<usart_address>::number-1>()();
        usart->SR = ~(USART_SR_TXE);
    }
}

void init_rcc(uint32_t usart_address)
{
    switch (usart_address)
    {
        #ifdef USART1_BASE
        case USART1_BASE:
        {
            RCC->APB2ENR = RCC->APB2ENR | hal::interfaces::detail::get_rcc_flag<1>();
            return;
        }
        #endif
        #ifdef USART2_BASE
        case USART2_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<2>();
            return;
        }
        #endif
        #ifdef USART3_BASE
        case USART3_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<3>();
            return;
        }
        #endif
        #ifdef UART4_BASE
        case UART4_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<4>();
            return;
        }
        #endif
        #ifdef UART5_BASE
        case UART5_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<5>();
            return;
        }
        #endif
        #ifdef USART6_BASE
        case USART6_BASE:
        {
            RCC->APB2ENR = RCC->APB2ENR | hal::interfaces::detail::get_rcc_flag<6>();
            return;
        }
        #endif
        #ifdef UART7_BASE
        case UART7_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<7>();
            return;
        }
        #endif
        #ifdef UART8_BASE
        case UART8_BASE:
        {
            RCC->APB1ENR = RCC->APB1ENR | hal::interfaces::detail::get_rcc_flag<8>();
            return;
        }
        #endif
        #ifdef UART9_BASE
        case UART9_BASE:
        {
            RCC->APB2ENR = RCC->APB2ENR | hal::interfaces::detail::get_rcc_flag<9>();
            return;
        }
        #endif
        #ifdef UART10_BASE
        case UART10_BASE:
        {
            RCC->APB2ENR = RCC->APB2ENR | hal::interfaces::detail::get_rcc_flag<10>();
            return;
        }
        #endif

    }
}

}

extern "C"
{
    #ifdef USART1_BASE
    void USART1_IRQHandler(void)
    {
        handle_usart<USART1_BASE>();
    }
    #endif

    #ifdef USART2_BASE
    void USART2_IRQHandler(void)
    {
        handle_usart<USART2_BASE>();
    }
    #endif

    #ifdef USART3_BASE
    void USART3_IRQHandler(void)
    {
        handle_usart<USART3_BASE>();
    }
    #endif

    #ifdef UART4_BASE
    void UART4_IRQHandler(void)
    {
        handle_usart<UART4_BASE>();
    }
    #endif

    #ifdef UART5_BASE
    void UART5_IRQHandler(void)
    {
        handle_usart<UART5_BASE>();
    }
    #endif

    #ifdef USART6_BASE
    void USART6_IRQHandler(void)
    {
        handle_usart<USART6_BASE>();
    }
    #endif

    #ifdef UART7_BASE
    void UART7_IRQHandler(void)
    {
        handle_usart<UART7_BASE>();
    }
    #endif

    #ifdef UART8_BASE
    void UART8_IRQHandler(void)
    {
        handle_usart<UART8_BASE>();
    }
    #endif

    #ifdef UART9_BASE
    void UART9_IRQHandler(void)
    {
        handle_usart<UART9_BASE>();
    }
    #endif

    #ifdef UART10_BASE
    void UART10_IRQHandler(void)
    {
        handle_usart<UART10_BASE>();
    }
    #endif
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

const IRQn_Type get_irqn(uint32_t usart_base)
{
    switch (usart_base)
    {

        #ifdef USART1_BASE
        case USART1_BASE: return detail::get_irq_v<IRQn_Type, 1>;
        #endif
        #ifdef USART2_BASE
        case USART2_BASE: return detail::get_irq_v<IRQn_Type, 2>;
        #endif
        #ifdef USART3_BASE
        case USART3_BASE: return detail::get_irq_v<IRQn_Type, 3>;
        #endif
        #ifdef UART4_BASE
        case UART4_BASE: return detail::get_irq_v<IRQn_Type, 4>;
        #endif
        #ifdef UART5_BASE
        case UART5_BASE: return detail::get_irq_v<IRQn_Type, 5>;
        #endif
        #ifdef USART6_BASE
        case USART6_BASE: return detail::get_irq_v<IRQn_Type, 6>;
        #endif
        #ifdef UART7_BASE
        case UART7_BASE: return detail::get_irq_v<IRQn_Type, 7>;
        #endif
        #ifdef UART8_BASE
        case UART8_BASE: return detail::get_irq_v<IRQn_Type, 8>;
        #endif
        #ifdef UART9_BASE
        case UART9_BASE: return detail::get_irq_v<IRQn_Type, 9>;
        #endif
        #ifdef UART10_BASE
        case UART10_BASE: return detail::get_irq_v<IRQn_Type, 10>;
        #endif
    }

    return detail::get_irq_v<IRQn_Type, -1>;
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

void Usart::Impl::set_baudrate(const uint32_t baudrate)
{
    set_baudrate(HAL_RCC_GetSysClockFreq(), baudrate);
}

void Usart::Impl::set_baudrate(const uint32_t bus_frequency, const uint32_t baudrate)
{
    usart_->BRR = bus_frequency / baudrate;
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



uint32_t get_alternate_function(uint32_t usart_address)
{
    switch (usart_address)
    {
        #ifdef USART1_BASE
        case USART1_BASE: return GPIO_AF7_USART1;
        #endif
        #ifdef USART2_BASE
        case USART2_BASE: return GPIO_AF7_USART2;
        #endif
        #ifdef USART3_BASE
        case USART3_BASE: return GPIO_AF7_USART3;
        #endif
        #ifdef UART4_BASE
        case UART4_BASE: return GPIO_AF8_UART4;
        #endif
        #ifdef UART5_BASE
        case UART5_BASE: return GPIO_AF8_UART5;
        #endif
        #ifdef USART6_BASE
        case USART6_BASE: return GPIO_AF8_USART6;
        #endif
        #ifdef UART7_BASE
        case UART7_BASE: return GPIO_AF8_UART7;
        #endif
        #ifdef UART8_BASE
        case UART8_BASE: return GPIO_AF8_UART8;
        #endif
        #ifdef UART9_BASE
        case UART9_BASE: return GPIO_AF11_UART9;
        #endif
        #ifdef UART10_BASE
        case UART10_BASE: return GPIO_AF11_UART10;
        #endif
    }
    return -1;
}

void Usart::Impl::init(const uint32_t baudrate)
{
    init_rcc(usart_.address());

    rx_.init(
        hal::gpio::Alternate::PushPull,
        hal::gpio::Speed::High,
        hal::gpio::PullUpPullDown::None);

    static_cast<hal::gpio::DigitalInputOutputPin::Impl*>(&rx_)
        ->set_alternate_function(get_alternate_function(usart_.address()));

    tx_.init(
        hal::gpio::Alternate::PushPull,
        hal::gpio::Speed::High,
        hal::gpio::PullUpPullDown::None);

    static_cast<hal::gpio::DigitalInputOutputPin::Impl*>(&tx_)
        ->set_alternate_function(get_alternate_function(usart_.address()));

    set_baudrate(baudrate);

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
