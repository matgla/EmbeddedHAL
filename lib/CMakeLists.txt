message(STATUS "Adding libraries")

include (../cmake/GitModules.cmake)

fetch_module(eul)
fetch_module(gsl/gsl)


execute_command("git submodule foreach git checkout master")
execute_command("git submodule foreach git pull")