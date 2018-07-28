#pragma once

#include <string_view>

namespace hal
{
namespace usart
{

// clang-format off
template <typename T>
concept bool UsartImpl = requires(T a)
{
    { a.init() } -> void;
    { a.write(char{}) } -> void;
    { a.write(std::string_view{})} -> void;
};
// clang-format on

template <UsartImpl UsartImplType>
class Usart
{
public:
    static void init()
    {
        UsartImplType::init();
    }

    static void write(const char byte)
    {
        UsartImplType::write(byte);
    }

    static void write(const std::string_view& data)
    {
        UsartImplType::write(data);
    }
};

} // namespace usart
} // namespace hal
