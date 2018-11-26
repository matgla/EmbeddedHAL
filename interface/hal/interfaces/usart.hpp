#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

namespace hal
{
namespace interfaces
{

// clang-format off
template <typename T>
concept bool UsartImpl = requires(T a)
{
    { a.init(uint32_t{}) } -> void;
    { a.write(char{}) } -> void;
    { a.write(gsl::span<const uint8_t>{})} -> void;
    // TODO: fix this concept
    // { a.onData()} -> void;
};
// clang-format on

template <UsartImpl UsartImplType>
class Usart
{
public:
    static void init(uint32_t baudrate)
    {
        UsartImplType::init(baudrate);
    }

    static void set_baudrate(uint32_t baudrate)
    {
        UsartImplType::set_baudrate(baudrate);
    }

    static void write(const char byte)
    {
        UsartImplType::write(byte);
    }

    static void write(const gsl::span<const uint8_t>& data)
    {
        UsartImplType::write(data);
    }

    static void write(const std::string_view& data)
    {
        UsartImplType::write(data);
    }

    template <typename CallbackType>
    static void onData(CallbackType&& onDataCallback)
    {
        UsartImplType::onData(onDataCallback);
    }
};

} // namespace interfaces
} // namespace hal
