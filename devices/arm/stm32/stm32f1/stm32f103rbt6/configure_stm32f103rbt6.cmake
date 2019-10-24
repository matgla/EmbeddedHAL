set(target_name hal_devices_arm_stm32f103rbt6)

add_library(${target_name} INTERFACE)
target_sources(${target_name}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/arm/stm32/stm32f1/stm32f103rbt6/gpio.hpp
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f1xx)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/arm/stm32/common)
target_link_libraries(${target_name} INTERFACE hal_stm32f1xx)
target_include_directories(${target_name} INTERFACE ${PROJECT_SOURCE_DIR}/src)

