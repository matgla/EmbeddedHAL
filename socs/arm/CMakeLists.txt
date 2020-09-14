# This file is part of EmbeddedHAL project.
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

execute_process(
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/generate_linker_script.py
    --input=${hal_generated_soc_path}/soc_config.json
    --output=${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE rc
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/scripts/generate_linker_script.py)

if (${rc})
    message (FATAL_ERROR "Linker script generation failure")
endif ()

set (linker_script ${CMAKE_CURRENT_BINARY_DIR}/linker_script.ld CACHE INTERNAL "" FORCE)
set (linker_scripts_directory ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "" FORCE)

include (${CMAKE_CURRENT_BINARY_DIR}/memory_config.cmake)

