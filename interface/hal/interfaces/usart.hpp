#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include <eul/function.hpp>

namespace hal
{
namespace interfaces
{

class Usart
{
public:
    class Impl;

    using StreamType = gsl::span<const uint8_t>;
    using OnDataCallback = eul::function<void(const uint8_t), sizeof(void*)>;
    using OnSentCallback = eul::function<void(), sizeof(void*)>;

    void init(const uint32_t baudrate);
    void deinit();
    void set_baudrate(const uint32_t baudrate);
    void write(const StreamType& data);
    void write(const std::string_view& str);
    void on_data(const OnDataCallback& callback);
    void on_sent(const OnSentCallback& callback);
    void enable_rx_interrupt();
    void enable_tx_interrupt();
    uint8_t read() const;
};

} // namespace interfaces
} // namespace hal
