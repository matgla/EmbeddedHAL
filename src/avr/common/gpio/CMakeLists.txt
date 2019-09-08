
add_library(hal_avr_gpio INTERFACE)

target_sources(hal_avr_gpio
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_gpio.hpp
)

target_include_directories(hal_avr_gpio
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

add_subdirectory(ports)
target_link_libraries(hal_avr_gpio
    INTERFACE
        hal_avr_common_gpio_ports
)