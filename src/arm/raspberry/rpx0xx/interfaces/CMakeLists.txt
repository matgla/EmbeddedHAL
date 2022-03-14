# This file is part of EmbeddedHAL project.
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


add_library(hal_rpx0xx_interfaces) 

target_sources(hal_rpx0xx_interfaces
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/rpx0xx_usart.hpp
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/rpx0xx_usart.cpp 
)

target_include_directories(hal_rpx0xx_interfaces 
    PRIVATE 
        $<TARGET_PROPERTY:hardware_uart,INTERFACE_INCLUDE_DIRECTORIES>
        ${PROJECT_SOURCE_DIR}/src 
)

target_link_libraries(hal_rpx0xx_interfaces
    PUBLIC 
        hal_interfaces_interfaces
    PRIVATE
        hal_rpx0xx_gpio
)


