cmake_minimum_required(VERSION 3.9)
project(EmbeddedHal NONE)

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

set(boards_path "${CMAKE_CURRENT_SOURCE_DIR}/boards")

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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureProject.cmake)

set (CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "" FORCE)

get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
    set (CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)
endif()

enable_language(CXX C ASM)

find_package(eul REQUIRED)
find_package(GSL REQUIRED)

# set(CMAKE_CXX_FLAGS_RELEASE ""  CACHE STRING "Some description" FORCE)
# set(CMAKE_C_FLAGS_RELEASE ""  CACHE STRING "Some description" FORCE)

set(interface_sources_path "${PROJECT_SOURCE_DIR}/interface/hal")

add_library(hal_interface INTERFACE)
target_sources(hal_interface INTERFACE
    ${interface_sources_path}/core/backupRegisters.hpp
    ${interface_sources_path}/core/core.hpp
    ${interface_sources_path}/core/criticalSection.hpp
    ${interface_sources_path}/core/mutex.hpp
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

add_subdirectory(src/common)
add_subdirectory(interface/hal/memory)

add_device_hal_library(hal_device_library)

add_library(hal INTERFACE)

target_link_libraries(hal INTERFACE ${hal_device_library} hal_flags)

if (BUILD_UT OR ENABLE_ST)
    add_subdirectory(test)
endif ()
