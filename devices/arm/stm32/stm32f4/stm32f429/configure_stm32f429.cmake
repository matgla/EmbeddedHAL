function (configure_device)
    message(STATUS "Configuring STM32F429")
    set(target_name hal_devices_arm_stm32_f429)

    add_library(${target_name} INTERFACE)
    target_sources(${target_name}
        INTERFACE
            ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/stm32f4xx_hal_conf.h
            ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/gpio.hpp
            ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/i2c.hpp
            ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/usart.hpp
    )

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f4xx)

    target_link_libraries(${target_name} INTERFACE hal_stm32f4xx)
    target_include_directories(${target_name} INTERFACE ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/)
    target_include_directories(stm32 PUBLIC ${PROJECT_SOURCE_DIR}/devices/arm/stm32/stm32f4/stm32f429/)
endfunction()
