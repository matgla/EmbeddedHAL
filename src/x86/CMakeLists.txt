if (${BOARD} STREQUAL "Simulator")
    set(path_to_specific_gpio_config "boards/x86/simulator/gpio_config.hpp")
    
    set(sources_path ${CMAKE_CURRENT_SOURCE_DIR}/../../src/x86/simulator)

    set(sources 
        ${sources_path}/time/x86_sleep.cpp
    )
endif ()

message("-- Generate config file: ${path_to_specific_gpio_config}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../../config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)

add_library(hal ${hal_interface} ${sources})

target_include_directories(hal 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../interface
        ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(hal PRIVATE gsl)

target_compile_options(hal PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fconcepts -Wswitch -Werror>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)