#include "arm/stm32/stm32f10x/interfaces/stm32f10x_usart.hpp"
#include "hal/interfaces/usart.hpp"

namespace hal
{
namespace interfaces
{
using Usart1 = Usart<hal::stm32f10x::interfaces::Usart1<hal::stm32f10x::interfaces::Usart1Mapping::Standard>>;
} // namespace interfaces
} // namespace hal
