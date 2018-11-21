function(get_device_info mcu mcu_family arch vendor)
    message(STATUS "Configuration of board: Stm32_Black_Pill")
    set(${mcu} "STM32F103C8T6" PARENT_SCOPE)
    set(${mcu_family} "STM32F1xx" PARENT_SCOPE)
    set(${arch} "ARM" PARENT_SCOPE)
    set(${vendor} "STM32" PARENT_SCOPE)
endfunction()

function(add_device_hal_library hal_device_library)
    set(${hal_device_library} "stm32_black_pill")
    set(hal_device_library ${hal_device_library} PARENT_SCOPE)
    set(path_to_specific_gpio_config "${PROJECT_SOURCE_DIR}/boards/arm/stm32_black_pill/gpio_config.hpp")
    set(path_to_specific_usart_config "${PROJECT_SOURCE_DIR}/boards/arm/stm32_black_pill/usart_config.hpp")

    message(STATUS "Generate config file: ${path_to_specific_gpio_config}")
    message(STATUS "Generate config file: ${path_to_specific_usart_config}")
    configure_file(${PROJECT_SOURCE_DIR}/config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/config/usart_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/usart.hpp @ONLY)

    add_library(${hal_device_library})

    set(source_path "${PROJECT_SOURCE_DIR}/boards/arm/stm32_black_pill")
    target_sources(${hal_device_library} PUBLIC
        ${path_to_specific_gpio_config}
    )
    target_sources(${hal_device_library} PRIVATE
        ${source_path}/board.cpp
    )

    target_include_directories(${hal_device_library} PUBLIC
        ${PROJECT_BINARY_DIR}/include)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/arm/stm32/common)
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f10x)

    target_link_libraries(${hal_device_library} PUBLIC hal_stm32f1xx gsl)

endfunction()