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

target_include_directories(hal_binary_info
    INTERFACE 
        $<TARGET_PROPERTY:pico_binary_info,INTERFACE_INCLUDE_DIRECTORIES> 

)

add_library(hal_external_irq INTERFACE)

target_include_directories(hal_external_irq 
    INTERFACE 
        $<TARGET_PROPERTY:hardware_irq,INTERFACE_INCLUDE_DIRECTORIES>
)


add_library(hal_external_gpio INTERFACE)

target_include_directories(hal_external_gpio 
    INTERFACE
        $<TARGET_PROPERTY:hardware_gpio,INTERFACE_INCLUDE_DIRECTORIES>
)

add_library(hal_external_public INTERFACE)

target_link_libraries(hal_external_public 
    INTERFACE
        pico_runtime
        hal_external_gpio
        pico_binary_info
        hardware_irq 
        hardware_gpio
        pico_printf
        pico_base_headers
        hardware_structs 
)

add_library(hal_external_flash INTERFACE)

target_link_libraries(hal_external_flash 
    INTERFACE 
        hardware_structs
        hardware_flash
)

add_library(hal_external_resets INTERFACE) 

target_link_libraries(hal_external_resets 
    INTERFACE 
        hardware_resets
)

add_library(hal_external_sync INTERFACE) 

target_link_libraries(hal_external_sync 
    INTERFACE 
        hardware_sync
)

add_library(hal_external_clocks INTERFACE) 

target_link_libraries(hal_external_clocks
    INTERFACE 
        hal_external_gpio 
)

target_include_directories(hal_external_clocks
    INTERFACE 
        $<TARGET_PROPERTY:hardware_clocks,INTERFACE_INCLUDE_DIRECTORIES>
)

add_library(hal_external_timer INTERFACE)

target_link_libraries(hal_external_timer 
    INTERFACE 
        hal_external_irq 
)

target_include_directories(hal_external_timer 
    INTERFACE 
        $<TARGET_PROPERTY:hardware_timer,INTERFACE_INCLUDE_DIRECTORIES>  
)

add_library(hal_external_interfaces INTERFACE) 

target_include_directories(hal_external_interfaces
    INTERFACE 
        $<TARGET_PROPERTY:hardware_uart,INTERFACE_INCLUDE_DIRECTORIES>
)

