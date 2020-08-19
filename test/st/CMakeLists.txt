add_executable(st_tests)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/nanotest/cmake")


set (test_sources
)

target_sources(st_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interrupt/systick_tests.cpp
)

target_link_libraries(st_tests
    PUBLIC
        hal
        hal_flags
)

target_include_directories(st_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MsTest/include
)

include (GenerateBinary)

generate_binary(st_tests ${vendor})
