message(STATUS "Adding libraries")

include (../cmake/GitModules.cmake)

fetch_module_with_path(lib/eul eul)
fetch_module_with_path(lib/gsl/gsl gsl/gsl)


execute_command("git submodule foreach git checkout master")
execute_command("git submodule foreach git pull")