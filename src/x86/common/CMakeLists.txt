set(library_name "hal_x86_common")

add_library(${library_name} INTERFACE)

target_include_directories(${library_name}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

add_subdirectory(memory)
add_subdirectory(time)
add_subdirectory(usart)

target_link_libraries(${library_name}
    INTERFACE
    -Wl,--whole-archive
        hal_x86_common_time
        hal_x86_common_memory
        hal_x86_common_usart
    -Wl,--no-whole-archive

)
