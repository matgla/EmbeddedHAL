add_library(hal_stm32f4xx_time)

target_sources(hal_stm32f4xx_time
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32f4xx_time.cpp
)

target_include_directories(hal_stm32f4xx_time
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f4xx_time
    PUBLIC
        stm32
        eul
)
