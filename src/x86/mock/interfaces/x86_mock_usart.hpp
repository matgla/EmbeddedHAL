#pragma once

#include <iostream>
#include <string_view>

#include <functional>

#include <gsl/span>

namespace hal
{
namespace x86
{
namespace mock
{
namespace interfaces
{

class X86MockUsart
{
public:
    using OnDataCallback = std::function<void(const uint8_t)>;

    static void init(int baudrate)
    {
        static_cast<void>(baudrate);
    }

    static void write(const std::string_view& str)
    {
        std::cout << str;
    }

    static void write(const gsl::span<const uint8_t>& str)
    {
        for (auto byte : str)
        {
            std::cout << static_cast<char>(byte);
        }
    }

    void on_data(const OnDataCallback& callback)
    {
        static_cast<void>(callback);
    }
};

} // namespace interfaces
} // namespace mock
} // namespace x86
} // namespace hal
