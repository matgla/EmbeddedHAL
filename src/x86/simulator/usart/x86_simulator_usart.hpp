#pragma once

#include <thread>
#include <functional>

#include <boost/asio/serial_port.hpp>

#include "x86/simulator/detail/tcp_server.hpp"

#include "hal/interfaces/usart.hpp"

namespace hal
{
namespace x86
{
namespace simulator
{
namespace usart
{

class UsartDriver : public hal::interfaces::UsartInterface
{
public:
    UsartDriver(const std::string_view& device)
        : io_(new boost::asio::io_service())
        , port_(*io_)
        , device_(device)
    {
    }

    UsartDriver(UsartDriver&& usart)
        : io_(std::move(usart.io_))
        , port_(*io_)
        , device_(usart.device_)
    {

    }

    ~UsartDriver()
    {
        if (port_.is_open())
        {
            port_.close();
            thread_.join();
        }
    }

    using CallbackType = std::function<void(uint8_t)>;

    void init(uint32_t baudrate) override
    {
        port_.open(std::string(device_));
        port_.set_option(boost::asio::serial_port_base::baud_rate(baudrate));

        startListening();

        thread_ = std::thread([this] {io_->run();});
    }

    void setBaudrate(uint32_t baudrate) override
    {
        (void)(baudrate);
    }

    void write(const StreamType& data) override
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

private:
    void write(const uint8_t byte)
    {
        uint8_t buffer[1];
        buffer[0] = byte;
        boost::system::error_code ec;
        port_.write_some(boost::asio::buffer(buffer, 1), ec);
    }

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
    std::unique_ptr<boost::asio::io_service> io_;
    boost::asio::serial_port port_;
    std::vector<uint8_t> buffer_;
    std::thread thread_;
    std::string_view device_;
};


} // namespace usart
} // namespace simulator
} // namespace x86
} // namespace hal
