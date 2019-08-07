#pragma once

#include <functional>

#include <boost/asio/serial_port.hpp>

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
    Usart()
        : port_(io_)
        {

        }

    using CallbackType = std::function<void(uint8_t)>;
    void init(uint32_t baudrate)
    {
        port_.open("/dev/ttyS0");
        port_.set_option(boost::asio::serial_port_base::baud_rate(baudrate));

        startListening();
    }

    void write(const char byte)
    {
        uint8_t buffer[1];
        buffer[0] = byte;
        boost::system::error_code ec;
        port_.write_some(boost::asio::buffer(buffer, 1), ec);
    }

    void write(const std::string_view& data)
    {
        for (auto byte : data)
        {
            write(byte);
        }
    }

    void onData(const CallbackType& callback)
    {
        on_data_ = callback;
    }

private:
    void startListening()
    {
        port_.async_read_some(
            boost::asio::buffer(buffer_, 256),
            [this](boost::system::error_code ec, std::size_t bytes_transferred)
            {
                (void)(bytes_transferred);
                if (ec)
                {
                    startListening();
                    return;
                }

                if (on_data_)
                {
                    for (auto byte : buffer_)
                    {
                        on_data_(byte);
                    }
                }
                buffer_.clear();
                startListening();
            }
        );
    }

    CallbackType on_data_;
    boost::asio::io_service io_;
    boost::asio::serial_port port_;
    std::vector<uint8_t> buffer_;
};


} // namespace usart
} // namespace simulator
} // namespace x86
} // namespace hal
