#include "x86/simulator/usart/x86_simulator_usart.hpp"
#include "hal/interfaces/usart.hpp"

namespace hal
{
namespace interfaces
{

static Usart<x86::simulator::usart::Usart<1234>> Usart1{};

} // namespace interfaces
} // namespace hal
