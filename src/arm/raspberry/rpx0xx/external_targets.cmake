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

add_library(hal_binary_info INTERFACE) 

target_link_libraries(hal_binary_info
    INTERFACE 
        pico_binary_info 

)

add_library(hal_external_irq STATIC)

target_link_libraries(hal_external_irq 
    PUBLIC 
        pico_binary_info
        hardware_irq 
        hal_external_gpio
)

add_library(hal_external_gpio STATIC)

target_link_libraries(hal_external_gpio 
    PUBLIC
        hal_external_irq
        hardware_gpio
)

add_library(hal_external_public STATIC)

target_link_libraries(hal_external_public 
    PUBLIC
        hal_external_gpio
        pico_runtime 
        pico_standard_link 
)

add_library(hal_external_resets INTERFACE) 

target_link_libraries(hal_external_resets 
    INTERFACE 
        hardware_resets
)

add_library(hal_external_clocks STATIC) 

target_link_libraries(hal_external_clocks
    PUBLIC 
        hardware_clocks
    PRIVATE 
        hal_external_irq
)

add_library(hal_external_timer STATIC)

target_link_libraries(hal_external_timer 
    PUBLIC 
        hardware_timer 
    PRIVATE 
        hal_external_irq
)

add_library(hal_external_interfaces STATIC) 

target_link_libraries(hal_external_interfaces
    PUBLIC 
        hardware_uart
        hal_external_resets 
        hal_external_clocks 
    PRIVATE 
        hal_external_gpio
        hal_external_irq
        hal_external_timer 
)
