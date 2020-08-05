set (library_name hal_memory)

add_library(${library_name} INTERFACE)

target_sources(${library_name}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/eeprom.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/flash.hpp
)

target_include_directories(${library_name} INTERFACE
    ${PROJECT_SOURCE_DIR}/interface
)

target_link_libraries(${library_name}
    INTERFACE
        GSL
)

target_compile_options(${library_name} INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
)
