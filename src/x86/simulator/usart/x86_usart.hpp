#pragma once

#include <thread>

#include "x86/simulator/detail/tcp_server.hpp"

namespace hal
{
namespace x86
{
namespace simulator
{
namespace usart
{

template <uint16_t port>
class Usart
{
public:
    static void init()
    {
    }

    static void write(const char byte)
    {
        server_.write({static_cast<uint8_t>(byte)});
    }

    static void write(const std::string_view& data)
    {
        std::vector<uint8_t> buffer(data.begin(), data.end());
        server_.write(buffer);
    }

private:
    inline static detail::TcpServer server_ = detail::TcpServer(port);
};


} // namespace usart
} // namespace simulator
} // namespace x86
} // namespace hal
