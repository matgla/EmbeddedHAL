
cmake_minimum_required(VERSION 3.9)

if (DEFINED STANDALONE)
    project(EmbeddedHal CXX C ASM)
    include(cmake/ConfigureProject.cmake)
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

if (NOT DEFINED linker_script)
    message(FATAL_ERROR "linker_script variable must be defined!")
endif ()

set(includes_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/hal")

set(includes 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/details/utils.hpp
    ${includes_dir}/core/backupRegisters.hpp
    ${includes_dir}/core/core.hpp
    ${includes_dir}/core/criticalSection.hpp
    ${includes_dir}/core/mutex.hpp
    ${includes_dir}/gpio/digitalOut.hpp
    ${includes_dir}/memory/eeprom.hpp
    ${includes_dir}/time/rtc.hpp
    ${includes_dir}/time/sleep.hpp
    ${includes_dir}/time/time.hpp
    ${includes_dir}/time/watchdog.hpp
    ${includes_dir}/utils/assert.hpp
)

if (${mcu_family} STREQUAL "STM32F10x")
    if (${board} STREQUAL "Stm32_Black_Pill")
        #set(path_to_specific_gpio_config "${CURRENT_CMAKE_DIR}/src/boards/stm32_black_pill/gpio
        #configure_file(./config/
    endif()
    add_subdirectory(./implementation/arm/common)
    add_subdirectory(./implementation/arm/stm32/common)
    add_subdirectory(./implementation/arm/stm32/stm32f10x)

    add_library(hal ${includes} ${sources})
    target_link_libraries(hal stm32)
elseif (${MCU_FAMILY} STREQUAL "X86")
    add_subdirectory(./implementation/x86)
else ()
    message(FATAL_ERROR "Not supported MCU family: ${MCU_FAMILY}")
endif ()

target_include_directories(hal PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(hal gsl)

target_compile_options(hal PUBLIC
    -fno-builtin
    -fdata-sections
    -fdata-sections 
    -ffunction-sections
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)
