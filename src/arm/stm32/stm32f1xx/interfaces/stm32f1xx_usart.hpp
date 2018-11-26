#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include <stm32f1xx.h>

#include <eul/function.hpp>
#include <eul/memory_ptr.hpp>

#include "hal/clock.hpp"
#include "hal/gpio.hpp"

namespace hal
{
namespace stm32f1xx
{
namespace interfaces
{

struct UsartConfig
{
    const uint32_t tx_pin;
    const uint32_t rx_pin;
    const uint32_t cts_pin;
    const uint32_t rts_pin;
    const uint32_t ct_pin;
};

enum class Usart1Mapping
{
    /* Tx - PA9, Rx - PA10 */
    Standard,
    /* Tx - PB6, Rx - PB7 */
    Alternate
};

using Usart2Mapping = Usart1Mapping;

enum class Usart3Mapping
{
    Standard,
    PartialAlternate,
    Alternate
};

template <typename Rx, typename Tx, typename Cts = void, typename Rts = void, typename Ct = void>
struct Pinout
{
    using RxPin  = Rx;
    using TxPin  = Tx;
    using CtsPin = Cts;
    using RtsPin = Rts;
    using CtPin  = Ct;
};

template <Usart1Mapping mapping>
constexpr auto get_pinout()
{
    if constexpr (mapping == Usart1Mapping::Standard)
    {
        return Pinout<hal::gpio::PA10, hal::gpio::PA9>{};
    }
    else if (mapping == Usart1Mapping::Alternate)
    {
        return Pinout<hal::gpio::PB7, hal::gpio::PB6>{};
    }
}

static eul::function<void(const uint8_t), 0> usart1_rx = [](const uint8_t data) {};


template <std::size_t usart_address>
class UsartCommon
{
public:
    template <typename RxPin, typename TxPin>
    constexpr static void init(uint32_t bus_frequency, uint32_t baudrate)
    {
        TxPin::Implementation::init(hal::gpio::Output::OutputPushPull,
                                    hal::gpio::Speed::Medium,
                                    hal::stm32f1xx::gpio::Function::Alternate);
        RxPin::init(hal::gpio::Input::InputFloating);

        set_baudrate(bus_frequency, baudrate);
        /* enable tx */
        usart_->CR1 |= USART_CR1_TE;
        /* enable rx */
        usart_->CR1 |= USART_CR1_RE;

        /* enable USART */
        usart_->CR1 |= USART_CR1_UE;

        /* enable Rx intterupt */
        usart_->CR1 |= USART_CR1_RXNEIE;
        NVIC_EnableIRQ(USART1_IRQn);
    }


    constexpr static void set_baudrate(uint32_t bus_frequency, uint32_t baudrate)
    {
        usart_->BRR = bus_frequency / baudrate;
    }

    static void write(const char byte)
    {
        wait_for_tx();

        usart_->DR = byte;
    }

    static void write(const gsl::span<const uint8_t>& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    static void write(const std::string_view& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    template <typename CallbackType>
    static void onData(CallbackType&& onDataCallback)
    {
        usart1_rx = onDataCallback;
    }

protected:
    constexpr static void wait_for_tx()
    {
        while (!(usart_->SR & USART_SR_TXE))
        {
        }
    }


    constexpr static eul::memory_ptr<USART_TypeDef> usart_ = eul::memory_ptr<USART_TypeDef>(usart_address);
};

template <Usart1Mapping usart_mapping>
class Usart1 : public UsartCommon<USART1_BASE>
{
public:
    using TxPin = typename decltype(get_pinout<usart_mapping>())::TxPin;
    using RxPin = typename decltype(get_pinout<usart_mapping>())::RxPin;
    constexpr static void init(uint32_t baudrate)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

        UsartCommon<USART1_BASE>::init<RxPin, TxPin>(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
    }

    constexpr static void set_baudrate(uint32_t baudrate)
    {
        UsartCommon<USART1_BASE>::set_baudrate(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
    }
};


} // namespace interfaces
} // namespace stm32f1xx
} // namespace hal