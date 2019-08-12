function(get_device_info mcu mcu_family arch vendor)
    message(STATUS "Configuration of board: x86_linux")
    set(${mcu} "none" CACHE STRING "MCU Name" FORCE)
    set(${mcu_family} "none" CACHE STRING "MCU family" FORCE)
    set(${arch} "x86" CACHE STRING "MCU architecture" FORCE)
    set(${vendor} "none" CACHE STRING "MCU vendor" FORCE)
endfunction()

function(add_device_hal_library hal_device_library)
    set(${hal_device_library} "x86_linux")
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

    set(source_path "${PROJECT_SOURCE_DIR}/boards/x86/linux")
    target_sources(${hal_device_library} PUBLIC
        ${path_to_specific_gpio_config}
        ${path_to_specific_usart_config}
        ${path_to_specific_clock_config}
    )
    target_sources(${hal_device_library} PRIVATE
        ${source_path}/board.cpp
        ${source_path}/clock_config.hpp
        ${source_path}/gpio_config.hpp
        ${source_path}/usart_config.hpp
    )

    target_include_directories(${hal_device_library} PUBLIC
        ${PROJECT_BINARY_DIR}/include)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/common)
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/linux)

    target_link_libraries(${hal_device_library} PUBLIC -Wl,--whole-archive hal_x86_linux -Wl,--no-whole-archive gsl)

endfunction()