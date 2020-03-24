#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>
#include <eul/function.hpp>


namespace hal
{
namespace interfaces
{

template <typename UsartImpl>
class Usart
{
public:
    using StreamType = gsl::span<const uint8_t>;

    static void init(uint32_t baudrate)
    {
        UsartImpl::init(baudrate);
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

    static void on_data(const eul::function<void(const uint8_t), sizeof(void*)>& callback)
    {
        UsartImpl::onData(callback);
    }
};

} // namespace interfaces
} // namespace hal
