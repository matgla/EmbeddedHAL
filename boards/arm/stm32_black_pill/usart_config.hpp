#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_usart.hpp"
#include "hal/interfaces/usart.hpp"

namespace hal
{
namespace interfaces
{

using Usart1 = Usart<hal::stm32f1xx::interfaces::Usart1<hal::stm32f1xx::interfaces::Usart1Mapping::Standard>>;

} // namespace interfaces
} // namespace hal
