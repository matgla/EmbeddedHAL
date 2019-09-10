#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace avr
{
namespace common
{
namespace interfaces
{

class AvrUsart
{
public:
    template <typename RxPin, typename TxPin>
    static void init(uint32_t baudrate)
    {
        initUsart(baudrate);
        initGpio<TxPin>();
    }

    static void setBaudrate(uint32_t baudrate);
    static void write(const gsl::span<uint8_t>& data);
    static void write(const std::string_view& str);
private:
    static void initUsart(uint32_t baudrate);
    template <typename TxPin>
    static void initGpio()
    {
        TxPin::init(hal::gpio::Input::InputPullUpDown);
    }
    static void write(uint8_t byte);
};

} // namespace interfaces
} // namespace common
} // namespace avr
} // namespace hal
