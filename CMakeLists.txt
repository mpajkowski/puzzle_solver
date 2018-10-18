cmake_minimum_required (VERSION 2.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (proj_name puzzle_solver)
project (${proj_name})
include_directories (inc)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
