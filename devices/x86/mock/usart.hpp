#pragma once

#include "hal/interfaces/usart.hpp"
#include "x86/mock/interfaces/x86_mock_usart.hpp"

namespace hal
{
namespace devices
{
namespace interfaces
{

using Usart1 = hal::interfaces::Usart<hal::x86::mock::interfaces::X86MockUsart>;

}
}
}

