add_library(hal_stm32f4xx_interrupts)

target_sources(hal_stm32f4xx_interrupts
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_pendsv.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_svc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_systick.cpp
)

target_include_directories(hal_stm32f4xx_interrupts
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f4xx_interrupts
    PUBLIC
        stm32
        eul
)
