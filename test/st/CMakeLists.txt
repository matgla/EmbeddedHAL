message (STATUS "flags: ${CMAKE_EXE_LINKER_FLAGS}")

set_property(DIRECTORY PROPERTY LINK_OPTIONS "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${hal_exe_linker_flags}")


add_executable(st_tests)

target_sources(st_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


target_link_libraries(st_tests
    PUBLIC
        hal
        hal_flags
)


# include (GenerateBinary)

# generate_binary(st_tests ${vendor})
