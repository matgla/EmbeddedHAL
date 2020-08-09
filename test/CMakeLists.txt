get_filename_component(root_dir ${PROJECT_SOURCE_DIR}/../.. ABSOLUTE)

if (BUILD_UT)
    find_package(gtest REQUIRED)

    add_subdirectory(ut)
endif ()

if (ENABLE_ST)
    add_subdirectory(st)
endif ()
