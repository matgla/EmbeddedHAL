// #pragma once

// #include <cstdint>
// #include <string_view>

// #include <gsl/span>
// #include <eul/function.hpp>


// namespace hal
// {
// namespace interfaces
// {

// class Usart
// {
// public:
//     using StreamType = gsl::span<const uint8_t>;
//     using OnDataCallback = eul::function<void(const uint8_t), sizeof(void*)>;

//     virtual void init(uint32_t baudrate) = 0;
//     virtual void set_baudrate(uint32_t baudrate) = 0;
//     virtual void write(const StreamType& data) = 0;
//     virtual void write(const std::string_view& str) = 0;
//     virtual void on_data(const OnDataCallback& callback) = 0;
// };

// } // namespace interfaces
// } // namespace hal
