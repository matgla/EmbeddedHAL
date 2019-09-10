set(target_name hal_devices_avr_attiny85)

set(HAS_PORT_A false CACHE INTERNAL "")
set(HAS_PORT_B true CACHE INTERNAL "")
set(HAS_PORT_C false CACHE INTERNAL "")
set(HAS_PORT_D false CACHE INTERNAL "")

add_library(${target_name} INTERFACE)

target_sources(${target_name}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/avr/attiny/attiny85/gpio.hpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/avr)

target_link_libraries(${target_name} INTERFACE hal_avr)
