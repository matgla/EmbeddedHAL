#pragma once

#include <iostream>
#include <string_view>

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
    static void write(const std::string_view& str)
    {
        std::cout << str;
    }
};

} // namespace interfaces
} // namespace mock
} // namespace x86
} // namespace hal
