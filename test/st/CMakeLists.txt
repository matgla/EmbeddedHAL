add_executable(st_tests)

target_sources(st_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(st_tests
    PUBLIC
        hal
)

# include (GenerateBinary)

# generate_binary(st_tests ${vendor})
