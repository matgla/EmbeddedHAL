add_executable(st_tests)

find_package(mstest REQUIRED)

target_sources(st_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/systick_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/svc_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/trigger_syscall.s
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/pendsv_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timer/timer_tests.cpp
)

target_link_libraries(st_tests
    PUBLIC
        hal
        hal_flags
        mstest
)

include (GenerateBinary)

generate_binary(st_tests ${vendor})
