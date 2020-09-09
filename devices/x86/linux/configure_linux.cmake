function (configure_device)
    set(target_name hal_devices_x86_linux)
    message(STATUS "Configuring X86 linux, name: ${target_name}")
    message(FATAL_ERROR "aaaa")
    add_library(${target_name} INTERFACE)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/common)
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/linux)
    target_link_libraries(${target_name} INTERFACE hal_x86_linux)
    target_include_directories(${target_name} INTERFACE ${PROJECT_SOURCE_DIR}/src)

endfunction()
