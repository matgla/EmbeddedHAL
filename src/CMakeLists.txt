message (STATUS "Configuring HAL")

include(FetchContent)

FetchContent_Declare(
  mspkg
  GIT_REPOSITORY https://github.com/matgla/mspkg.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(mspkg)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mspkg_SOURCE_DIR}/cmake)
include (mspkg)

setup_mspkg(${mspkg_SOURCE_DIR})

if (BUILD_UT)
    message (STATUS "Configuring HAL for UT")
    set (BOARD "x86_mock" CACHE STRING "Board name" FORCE)
endif ()

set(boards_path "${PROJECT_SOURCE_DIR}/boards")

find_package(Git QUIET)
if (NOT GIT_FOUND)
    message (FATAL_ERROR "Can't find git")
endif ()

message(STATUS "Fetching dependency: EmbeddedCmakes")
execute_process(
    COMMAND
        git submodule update --init -- cmake
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_QUIET
    ERROR_QUIET
)

execute_process(
    COMMAND
        git checkout master
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    OUTPUT_QUIET
    ERROR_QUIET
)

execute_process(
    COMMAND
        git pull
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    OUTPUT_QUIET
    ERROR_QUIET
)

find_package(EmbeddedCMake REQUIRED)

include(ConfigureProject)
enable_language(CXX C ASM)

message("mcu: ${mcu}")

find_package (Python COMPONENTS Interpreter)

message ("${board_configuration_file}")
set (arguments
    --board=${board_configuration_file}
    --input=${PROJECT_SOURCE_DIR}/socs
    --output=${CMAKE_CURRENT_BINARY_DIR}/generated_soc
)

set (hal_generated_soc_path ${CMAKE_CURRENT_BINARY_DIR}/generated_soc CACHE INTERNAL "")

if (user_socs_config)
    set (arguments ${arguments} --user_directory=${user_socs_config})
endif ()

if (hal_user_config_file)
    set (arguments ${arguments} --user_configs=${hal_user_config_file})
endif ()

message ("${arguments}")

execute_process(
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/generate_soc.py ${arguments}
    RESULT_VARIABLE rc
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/scripts/generate_soc.py)

include (${CMAKE_CURRENT_BINARY_DIR}/generated_soc/soc_config.cmake)
set (soc_config_path ${CMAKE_CURRENT_BINARY_DIR}/generated_soc/soc_config.json CACHE INTERNAL "" FORCE)

if (${rc})
    message (FATAL_ERROR "SOC generation failed")
endif ()

set (CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX})

get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
    set (CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)
endif()

find_package(eul REQUIRED)
find_package(GSL REQUIRED)

set(interface_sources_path "${PROJECT_SOURCE_DIR}/interface/hal")

add_library(hal_interface INTERFACE)
target_sources(hal_interface INTERFACE
    ${interface_sources_path}/core/backupRegisters.hpp
    ${interface_sources_path}/core/core.hpp
    ${interface_sources_path}/core/criticalSection.hpp
    ${interface_sources_path}/memory/eeprom.hpp
    ${interface_sources_path}/time/rtc.hpp
    ${interface_sources_path}/time/sleep.hpp
    ${interface_sources_path}/time/time.hpp
    ${interface_sources_path}/time/watchdog.hpp
    ${interface_sources_path}/utils/assert.hpp
    ${interface_sources_path}/common/timer/interval_timer.hpp
    ${interface_sources_path}/common/timer/ITimer.hpp
    ${interface_sources_path}/common/timer/observed_timer.hpp
    ${interface_sources_path}/common/timer/timeout_timer.hpp
    ${interface_sources_path}/common/timer/timer_manager.hpp
    ${interface_sources_path}/common/timer/timer.hpp
    ${interface_sources_path}/interrupt/pendsv.hpp
    ${interface_sources_path}/interrupt/systick.hpp
    ${interface_sources_path}/interrupt/svc.hpp
)

target_include_directories(hal_interface INTERFACE
    ${PROJECT_SOURCE_DIR}/interface
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(hal_interface INTERFACE GSL eul)

add_subdirectory(common)

find_package (Python COMPONENTS Interpreter)

execute_process(
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/generate_board.py
    --input=${soc_config_path}
    --user_config=${board_configuration_path}
    --output=${CMAKE_CURRENT_BINARY_DIR}/generated_board
    RESULT_VARIABLE rc
)

if (${rc})
    message (FATAL_ERROR "Can't generate board from: ${soc_config_path}")
endif ()

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/scripts/generate_board.py)

execute_process(
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/generator/generate_soc_library.py
    --input=${soc_config_path}
    --output=${CMAKE_CURRENT_BINARY_DIR}/generated_soc
    RESULT_VARIABLE rc
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/scripts/generator/generate_soc_library.py)

if (${rc})
    message (FATAL_ERROR "Can't generate soc library from: ${soc_config_path}")

endif ()

include (${CMAKE_CURRENT_BINARY_DIR}/generated_board/board.cmake)

add_library(hal INTERFACE)

target_link_libraries(hal INTERFACE hal_interface board hal_flags)

