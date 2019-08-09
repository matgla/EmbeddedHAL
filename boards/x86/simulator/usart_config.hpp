#pragma once

#include "x86/simulator/usart/x86_simulator_usart.hpp"
#include "boards/containers/usart_container.hpp"
#include "boards/containers/drivers_pack.hpp"
#include "boards/containers/driver_holder.hpp"

namespace hal
{
namespace board
{

class Usart0;
class Usart1;

static auto UsartContainer = hal::boards::make_usart_container(hal::boards::DriversPack(
    hal::boards::make_holder<Usart0>(x86::simulator::usart::UsartDriver("/dev/ttyS0")),
    hal::boards::make_holder<Usart1>(x86::simulator::usart::UsartDriver("/dev/ttyS1"))
));

} // namespace board
} // namespace hal
