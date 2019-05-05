set (library_name hal_memory)

add_library(${library_name} INTERFACE)

target_sources(${library_name}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/eeprom.hpp
)

target_include_directories(${library_name} INTERFACE
    ${PROJECT_SOURCE_DIR}/interface
)
