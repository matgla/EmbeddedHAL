#pragma once

#include <iostream>
#include <string_view>

#include <functional>

#include <gsl/span>

#include "x86/mock/interfaces/x86_mock_usart.hpp"

namespace hal
{
namespace x86
{
namespace mock
{
namespace interfaces
{

static void X86MockUsart::init(int baudrate)
{
    static_cast<void>(baudrate);
}

static void X86MockUsart::write(const std::string_view& str)
{
    std::cerr << "Write aa: " << str << std::endl;

    std::cout << str;
}

static void X86MockUsart::write(const gsl::span<const uint8_t>& str)
{
    std::cerr << "Write aaa: " << std::endl;
    for (auto byte : str)
    {
        std::cerr << "->" << byte << std::endl;
        std::cout << static_cast<char>(byte);
    }
}

void X86MockUsart::on_data(const OnDataCallback& callback)
{
    static_cast<void>(callback);
}

} // namespace interfaces
} // namespace mock
} // namespace x86
} // namespace hal
