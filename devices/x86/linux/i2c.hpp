#pragma once

#include "x86/mock/interfaces/x86_mock_i2c.hpp"


namespace hal
{

namespace interfaces
{
using I2C = hal::x86::mock::interfaces::X86I2CMock;
} // namespace interfaces

namespace devices
{
namespace interfaces
{

using I2C_1 = hal::interfaces::I2C;

}
}
}

