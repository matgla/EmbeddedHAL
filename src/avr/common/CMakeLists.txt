
add_library(hal_avr_common INTERFACE)

add_subdirectory(gpio)
add_subdirectory(interfaces)
add_subdirectory(time)

target_link_libraries(hal_avr_common
    INTERFACE
        hal_avr_gpio
        hal_avr_time
        hal_avr_interfaces
)
