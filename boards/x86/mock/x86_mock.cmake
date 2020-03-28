function(get_device_info mcu mcu_family arch vendor)
    message(STATUS "Configuration of board: x86_mock")
    set(${mcu} "none" PARENT_SCOPE)
    set(${mcu_family} "none" PARENT_SCOPE)
    set(${arch} "x86" PARENT_SCOPE)
    set(${vendor} "none" PARENT_SCOPE)
endfunction()

function(add_device_hal_library hal_device_library)
    set(${hal_device_library} "x86_mock")
    set(hal_device_library ${hal_device_library} PARENT_SCOPE)
    set(path_to_specific_gpio_config "${PROJECT_SOURCE_DIR}/boards/x86/mock/gpio_config.hpp")
    set(path_to_specific_usart_config "${PROJECT_SOURCE_DIR}/boards/x86/mock/usart_config.hpp")
    set(path_to_specific_clock_config "${PROJECT_SOURCE_DIR}/boards/x86/mock/clock_config.hpp")

    message(STATUS "Generate config file: ${path_to_specific_gpio_config}")
    message(STATUS "Generate config file: ${path_to_specific_usart_config}")
    message(STATUS "Generate config file: ${path_to_specific_clock_config}")
    configure_file(${PROJECT_SOURCE_DIR}/config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/config/usart_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/usart.hpp @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/config/clock_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/clock.hpp @ONLY)

    add_library(${hal_device_library})

    set(source_path "${PROJECT_SOURCE_DIR}/boards/x86/mock")
    target_sources(${hal_device_library} PUBLIC
        ${path_to_specific_gpio_config}
        ${path_to_specific_usart_config}
        ${path_to_specific_clock_config}
    )
    target_sources(${hal_device_library} PRIVATE
        ${source_path}/board.cpp
    )

    target_include_directories(${hal_device_library} PUBLIC
        ${PROJECT_BINARY_DIR}/include)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/mock)

    target_link_libraries(${hal_device_library} PUBLIC -Wl,--whole-archive hal_x86_mock -Wl,--no-whole-archive gsl)

    target_compile_options(${hal_device_library} PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    )

endfunction()
