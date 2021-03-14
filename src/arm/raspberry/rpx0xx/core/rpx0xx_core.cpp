// This file is part of embeddedHAL project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <hal/core/core.hpp>

#include <hardware/structs/xosc.h>
#include <hardware/structs/clocks.h>
#include <hardware/regs/resets.h>

#include <hal/core/clock_units.hpp>
#include <arm/raspberry/rpx0xx/core/rpx0xx_register_manipulator.hpp>
#include <arm/raspberry/rpx0xx/core/rpx0xx_reset.hpp>

namespace hal 
{
namespace core 
{

namespace 
{

void wait_for_clock(clock_index index)
{
    while (clocks_hw->clk[index].selected != 0x1);
}

void initialize_system_clock() 
{
    AtomicRegister sysclk_ctrl(&clocks_hw->clk[clk_sys].ctrl);
    sysclk_ctrl.clear_bits(CLOCKS_CLK_SYS_CTRL_BITS);
    wait_for_clock(clk_sys);

    AtomicRegister refclk_ctrl(&clocks_hw->clk[clk_ref].ctrl);
    refclk_ctrl.clear_bits(CLOCKS_CLK_REF_CTRL_SRC_BITS);
    wait_for_clock(clk_ref);

    uint32_t reset_mask = RESETS_RESET_PLL_SYS_BITS 
        | RESETS_RESET_PLL_USB_BITS;

    reset_on(reset_mask);
    reset_off_and_wait(reset_mask);
}

}

void Core::initialize_oscillator()
{
    xosc_hw->ctrl = XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ;

    constexpr uint32_t osc_freq = 12_MHz; 
    constexpr uint32_t startup_delay = osc_freq / 1000 / 256;

    AtomicRegister xosc(&xosc_hw->ctrl);
    xosc.set_bits(XOSC_CTRL_ENABLE_VALUE_ENABLE << XOSC_CTRL_ENABLE_LSB);

    while (!(xosc_hw->status & XOSC_STATUS_STABLE_BITS));
}

void Core::initialize_clocks()
{
    clocks_hw->resus.ctrl = 0;

    initialize_oscillator();

    
}

} // namespace core
} // namespace hal
