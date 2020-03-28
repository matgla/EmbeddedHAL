function (configure_device)
    message(STATUS "Configuring X86 mock")
    set(target_name hal_devices_x86_mock)

    add_library(${target_name} INTERFACE)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/x86/mock)
    target_link_libraries(${target_name} INTERFACE hal_x86_mock)
    target_include_directories(${target_name} INTERFACE ${PROJECT_SOURCE_DIR}/src)
endfunction()
