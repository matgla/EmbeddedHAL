add_library(hal_stm32f4xx_core)

target_sources(hal_stm32f4xx_core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_critical_section.cpp
)

target_include_directories(hal_stm32f4xx_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f4xx_core
    PUBLIC
        stm32
)
