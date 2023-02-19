cmake_minimum_required(VERSION 3.22)
project(linalg_project)


set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE headers *.hpp *.h *.cpp)
add_library(linalg_project_library INTERFACE ${headers})

add_executable(linalg_main solver.cpp)