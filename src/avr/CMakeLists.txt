set(sources_path ${PROJECT_SOURCE_DIR}/src/avr)

add_library(hal_avr INTERFACE)

target_include_directories(hal_avr
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

add_subdirectory(gpio)

target_link_libraries(hal_avr
    INTERFACE
        avr
        avr_libstdcpp
        hal_avr_gpio
)
