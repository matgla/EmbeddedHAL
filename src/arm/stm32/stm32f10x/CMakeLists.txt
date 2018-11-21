if (${BOARD} STREQUAL "Stm32_Black_Pill")
    set(path_to_specific_gpio_config "boards/stm32/stm32_black_pill/gpio_config.hpp")
    set(sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f10x)

    set(sources
        ${sources_path}/time/rtc_stm32.cpp
    )
endif()

message("-- Generate config file: ${path_to_specific_gpio_config}")
configure_file(${PROJECT_SOURCE_DIR}/config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)

add_library(hal ${sources})

target_include_directories(hal
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal PUBLIC stm32_hal_common)
