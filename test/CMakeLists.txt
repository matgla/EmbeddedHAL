get_filename_component(root_dir ${PROJECT_SOURCE_DIR}/../.. ABSOLUTE)

include (${root_dir}/cmake/GitModules.cmake)
fetch_module_via_tag(test/ut/lib/googletest ${root_dir}/test/ut/lib/googletest ${root_dir} "release-1.10.0")
add_subdirectory(ut)

