#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>


namespace hal
{
namespace interfaces
{

template <typename UsartImpl>
class Usart
{
public:
    using StreamType = gsl::span<const uint8_t>;

    template <typename RxPin, typename TxPin>
    static void init(uint32_t baudrate)
    {
        UsartImpl::template init<RxPin, TxPin>(baudrate);
    }

    static void setBaudrate(uint32_t baudrate)
    {
        UsartImpl::setBaudrate(baudrate);
    }

    static void write(const StreamType& data)
    {
        UsartImpl::write(data);
    }

    static void write(const std::string_view& str)
    {
        UsartImpl::write(str);
    }
};

} // namespace interfaces
} // namespace hal
