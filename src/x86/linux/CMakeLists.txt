set(sources_path ${PROJECT_SOURCE_DIR}/src/x86/linux)
set(library_name "hal_x86_linux")

add_library(${library_name} STATIC)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_sources(${library_name}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/x86_mock_usart.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/x86_mock_usart.cpp
)

target_link_libraries(${library_name}
    PUBLIC
        hal_x86_common
)
