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
        , port_(new boost::asio::serial_port(*io_))
        , device_(device)
    {
    }

    UsartDriver(UsartDriver&& usart)
        : io_(std::move(usart.io_))
        , port_(std::move(usart.port_))
        , thread_(std::move(usart.thread_))
        , device_(usart.device_)
    {

    }

    ~UsartDriver()
    {
        if (port_ != nullptr && port_->is_open())
        {
            port_->cancel();
            port_->close();

            io_->stop();
            thread_.join();
        }
    }

    void init(uint32_t baudrate) override
    {
        port_->open(std::string(device_));
        port_->set_option(boost::asio::serial_port_base::baud_rate(baudrate));

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
        port_->write_some(boost::asio::buffer(buffer, 1), ec);
    }

    void startListening()
    {
        if (port_ == nullptr || !port_->is_open())
        {
            return;
        }
        port_->async_read_some(
            boost::asio::buffer(buffer_, 256),
            [this](boost::system::error_code ec, std::size_t bytes_transferred)
            {
                if (!bytes_transferred)
                {
                    startListening();
                    return;
                }

                if (ec)
                {
                    startListening();
                    return;
                }

                on_data_signal_.emit(gsl::make_span(buffer_, bytes_transferred));

                startListening();
            }
        );
    }

    std::unique_ptr<boost::asio::io_service> io_;
    std::unique_ptr<boost::asio::serial_port> port_;
    uint8_t buffer_[256];
    std::thread thread_;
    std::string_view device_;
};


} // namespace usart
} // namespace simulator
} // namespace x86
} // namespace hal
