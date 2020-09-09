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

    static void init(int baudrate);
    static void write(const std::string_view& str);
    static void write(const gsl::span<const uint8_t>& str);
    void on_data(const OnDataCallback& callback);
};

} // namespace interfaces
} // namespace mock
} // namespace x86
} // namespace hal
