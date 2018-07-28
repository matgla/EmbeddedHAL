#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <thread>
#include <utility>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace hal
{
namespace x86
{
namespace simulator
{
namespace detail
{

struct Session : public std::enable_shared_from_this<Session>
{

    Session(tcp::socket socket)
        : socket_(std::move(socket))
    {
    }

    void start()
    {
        read();
    }

    void write(const std::vector<uint8_t>& data)
    {
        if (!socket_.is_open())
        {
            return;
        }
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data.data(), data.size()),
                                 [this, self](boost::system::error_code ec, std::size_t length) {
                                     if (!ec)
                                     {
                                         //read();
                                     }
                                 });
    }

private:
    void read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
                                    {
                                        std::cout << "Client disconnected on port: " << socket_.remote_endpoint().port() << std::endl;
                                        socket_.close();
                                        //do_write(length);
                                    }
                                });
    }

    enum
    {
        max_length = 1024
    };

    tcp::socket socket_;
    std::vector<uint8_t> data_;
};

class TcpServer
{
public:
    TcpServer(short port)
        : acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)), socket_(io_service_), port_(port)
    {
        do_accept();
        thread_ = std::thread([this] { io_service_.run(); });
    }

    ~TcpServer()
    {
        if (socket_.is_open())
        {
            socket_.close();
            thread_.join();
        }
    }

    void write(const std::vector<uint8_t>& data)
    {
        if (session_)
        {
            session_->write(data);
        }
    }

private:
    void do_accept()
    {
        std::cout << "USART server started. Waiting for connection on: " << port_ << std::endl;
        acceptor_.async_accept(socket_,
                               [this](boost::system::error_code ec) {
                                   if (!ec)
                                   {
                                       std::cout << "Received connection on: " << port_ << std::endl;
                                       session_ = std::make_shared<Session>(std::move(socket_));
                                       session_->start();
                                   }
                                   do_accept();
                               });
    }

    boost::asio::io_service io_service_;
    std::shared_ptr<Session> session_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::thread thread_;
    short port_;
};

} // namespace detail
} // namespace simulator
} // namespace x86
} // namespace hal
