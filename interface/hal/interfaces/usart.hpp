#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

namespace hal
{
namespace interfaces
{

template <typename UsartImplType>
class Usart
{
public:
    void init(uint32_t baudrate)
    {
        impl_.init(baudrate);
    }

    void set_baudrate(uint32_t baudrate)
    {
        impl_.set_baudrate(baudrate);
    }

    void write(const char byte)
    {
        impl_.write(byte);
    }

    void write(const gsl::span<const uint8_t>& data)
    {
        impl_.write(data);
    }

    void write(const std::string_view& data)
    {
        impl_.write(data);
    }

    template <typename CallbackType>
    void onData(CallbackType&& onDataCallback)
    {
        impl_.onData(onDataCallback);
    }
private:
    UsartImplType impl_;
};

} // namespace interfaces
} // namespace hal
