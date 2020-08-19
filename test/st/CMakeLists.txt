add_executable(st_tests)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/nanotest/cmake")

find_package(mstest REQUIRED)

target_sources(st_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/systick_tests.cpp
)

target_link_libraries(st_tests
    PUBLIC
        hal
        hal_flags
        mstest
)

include (GenerateBinary)

generate_binary(st_tests ${vendor})
