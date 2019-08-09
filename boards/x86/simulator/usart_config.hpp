#pragma once

#include "x86/simulator/usart/x86_simulator_usart.hpp"
#include "hal/boards/containers/usart_container.hpp"
#include "hal/boards/containers/drivers_pack.hpp"
#include "hal/boards/containers/driver_holder.hpp"

namespace hal
{
namespace board
{

class Usart0;
class Usart1;

static UsartContainer = hal::boards::make_usart_container(hal::boards::DriverPack(
    hal::boards::make_holder<Usart0>(x86::simulator::usart::Usart("/dev/ttyS0")),
    hal::boards::make_holder<Usart1>(x86::simulator::usart::Usart("/dev/ttyS1"))
));

} // namespace board
} // namespace hal
