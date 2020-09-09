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

class X86I2CMock
{
public:

    static void init()
    {

    }

    static void write(uint8_t byte)
    {
        static_cast<void>(byte);
    }

    static void write(const std::string_view& str)
    {
        std::cout << str;
    }

    static void stop()
    {

    }

    static void start(uint8_t address)
    {
        static_cast<void>(address);
    }

    static void initialize_dma(void* buffer)
    {
        static_cast<void>(buffer);
    }

    static void dma_write(uint32_t size)
    {
        static_cast<void>(size);
    }

    static bool busy()
    {
        return false;
    }
};

} // namespace interfaces
} // namespace mock
} // namespace x86
} // namespace hal
