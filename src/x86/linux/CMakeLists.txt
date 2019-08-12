set(sources_path ${PROJECT_SOURCE_DIR}/src/x86/linux)
set(library_name "hal_x86_linux")

add_library(${library_name} INTERFACE)

target_include_directories(${library_name}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

add_subdirectory(../simulator)

target_link_libraries(${library_name}
    INTERFACE
        hal_x86_common
        hal_x86_simulator
)
