# This file is part of MSOS project.
# Copyright (C) 2020 Mateusz Stadnik
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

add_library(hal_common_utils INTERFACE)

target_sources(hal_common_utils
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/usart_printer.hpp
)

target_include_directories(hal_common_utils
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(hal_common_utils
    INTERFACE
        GSL
        hal_flags
)

#target_compile_options(hal_common_utils
#    INTERFACE
#        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wall -Werror -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -Wpointer-arith -Wcast-qual -Wno-missing-braces>
#        $<$<CONFIG:DEBUG>:-Og -g>
#        $<$<CONFIG:RELEASE>:-Os>
#)

