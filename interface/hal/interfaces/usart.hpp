#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include <eul/signals/signal.hpp>

namespace hal
{
namespace interfaces
{

class UsartInterface
{
public:
    using StreamType = gsl::span<const uint8_t>;
private:
    using OnDataSignal = eul::signals::signal<void(const StreamType&)>;
public:
    using OnDataSlot = OnDataSignal::slot_t;

    virtual ~UsartInterface() = default;

    virtual void init(uint32_t baudrate) = 0;
    virtual void setBaudrate(uint32_t baudrate) = 0;
    virtual void write(const StreamType& data) = 0;

    void onData(OnDataSlot& slot)
    {
        on_data_signal_.connect(slot);
    }
protected:
    OnDataSignal on_data_signal_;
};

} // namespace interfaces
} // namespace hal
