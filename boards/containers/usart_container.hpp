#pragma once

#include "hal/interfaces/usart.hpp"

#include "boards/containers/driver_container.hpp"

namespace hal
{
namespace boards
{

template <typename DriverPack>
DriverContainer<hal::interfaces::UsartInterface, DriverPack> make_usart_container(DriverPack&& drivers)
{
    return DriverContainer<hal::interfaces::UsartInterface, DriverPack>(std::move(drivers));
}

} // namespace boards
} // namespace hal
