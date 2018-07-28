#include "hal/usart/usart.hpp"
#include "x86/simulator/usart/x86_usart.hpp"

namespace hal
{
namespace usart
{

using USART1 = x86::simulator::usart::Usart<4001>;
using USART2 = x86::simulator::usart::Usart<4002>;
using USART3 = x86::simulator::usart::Usart<4003>;

} //namespace usart
} //namespace hal
