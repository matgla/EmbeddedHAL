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

add_library(hal_rpx0xx_gpio)

target_sources(hal_rpx0xx_gpio
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/rpx0xx_gpio.hpp 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/rpx0xx_gpio.cpp
)

target_link_libraries(hal_rpx0xx_gpio 
    PUBLIC 
        hal_interface
    PRIVATE
        hal_rpx0xx_core
)

target_include_directories(hal_rpx0xx_gpio
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
    PUBLIC 
        $<TARGET_PROPERTY:hardware_gpio,INTERFACE_INCLUDE_DIRECTORIES>
)

