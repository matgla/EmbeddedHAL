
#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

// #include <stm32f4xx.h>

#include <eul/function.hpp>
#include <eul/memory_ptr.hpp>

#include "hal/interfaces/usart.hpp"
#include "hal/clock/clock.hpp"
#include "hal/gpio/digital_input_output_pin.hpp"

inline void set_rx(const eul::function<void(uint8_t), sizeof(void*)>& callback)
{
    static_cast<void>(callback);
}

namespace hal
{
namespace stm32f4xx
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

class UsartCommon
{
public:
    using OnDataCallback = eul::function<void(const uint8_t), sizeof(void*)>;
    using StreamType = gsl::span<const uint8_t>;

    UsartCommon(uint32_t usart_address)
    {
        static_cast<void>(usart_address);
    }

    virtual void init(uint32_t baudrate) = 0;

    template <typename RxPin, typename TxPin>
    constexpr void init(uint32_t bus_frequency, uint32_t baudrate)
    {
        static_cast<void>(bus_frequency);
        static_cast<void>(baudrate);
    }



    void set_baudrate(uint32_t bus_frequency, uint32_t baudrate)
    {
        static_cast<void>(bus_frequency);
        static_cast<void>(baudrate);
    }

    void write(const char byte)
    {
        static_cast<void>(byte);
        wait_for_tx();

        if (!was_initialized)
        {
            return;
        }
        wait_for_tx();
    }

    void write(const gsl::span<const uint8_t>& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    void write(const std::string_view& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    void on_data(const OnDataCallback& callback)
    {
        set_rx(callback);
    }

protected:
    void wait_for_tx()
    {
    }

    bool was_initialized = false;
    // eul::memory_ptr<USART_TypeDef> usart_;
};

template <typename Rx, typename Tx, Usart1Mapping mapping>
class Usart1 : public UsartCommon
{
public:
    using TxPin = Tx;
    using RxPin = Rx;
    Usart1() : UsartCommon(0)
    {

    }
    void init(uint32_t baudrate) override
    {

    }

    void set_baudrate(uint32_t baudrate)
    {
    }
};


} // namespace interfaces
} // namespace stm32f4xx
} // namespace hal
