
add_library(hal_avr_common INTERFACE)

add_subdirectory(gpio)

target_link_libraries(hal_avr_common
    INTERFACE
        hal_avr_gpio
)
