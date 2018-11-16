if (${BOARD} STREQUAL "Stm32_Black_Pill")
    set(path_to_specific_gpio_config "boards/stm32/stm32_black_pill/gpio_config.hpp")
    set(sources_path ${CMAKE_CURRENT_SOURCE_DIR}/../../../arm/stm32/stm32f10x)

    set(sources
        ${sources_path}/time/stm32_sleep.cpp
    )
endif()

message("-- Generate config file: ${path_to_specific_gpio_config}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../../../../config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)

add_library(hal ${hal_interface} ${sources})

target_include_directories(hal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../interface
        ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(hal PUBLIC stm32)

target_compile_options(hal PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fconcepts -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fconcepts -fno-threadsafe-statics>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)

include(../../../../cmake/AddTargetCompileOptions.cmake)
add_target_compile_options(hal)