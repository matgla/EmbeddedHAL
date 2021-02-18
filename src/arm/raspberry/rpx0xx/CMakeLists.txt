# This file is part of MSBOOT project.
# Copyright (C) 2021 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

add_library(hal_rpx0xx STATIC) 

add_subdirectory(gpio)
add_subdirectory(interfaces)
add_subdirectory(syscalls)
add_subdirectory(time) 

target_link_libraries(hal_rpx0xx
    PUBLIC 
        pico_standard_link
        hal_rpx0xx_gpio
        hal_rpx0xx_interfaces
        hal_rpx0xx_time
        #hal_rpx0xx_syscalls
        hal_flags
)

if (HAL_INCLUDE_PICO_RUNTIME)

target_link_libraries(hal_rpx0xx
    PUBLIC 
        pico_binary_info
        hardware_irq
        hardware_gpio
        pico_runtime
)

endif ()
