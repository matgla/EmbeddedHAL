add_library(hal_avr_time)

target_sources(hal_avr_time
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_sleep.cpp
)

target_include_directories(hal_avr_time
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_avr_time
    PUBLIC
        avr
)