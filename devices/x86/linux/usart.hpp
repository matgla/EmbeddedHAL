#pragma once

#include "x86/mock/interfaces/x86_mock_usart.hpp"

namespace hal
{
namespace interfaces
{
    using Usart = hal::x86::mock::interfaces::X86MockUsart;
} // namespace interfaces
namespace devices
{
namespace interfaces
{

using Usart1 = hal::interfaces::Usart;

}
}
}

