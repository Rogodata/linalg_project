cmake_minimum_required(VERSION 3.22)
project(linalg_project)


set(CMAKE_CXX_STANDARD 23)
add_subdirectory(test)
add_subdirectory(source)

add_executable(linalg_project source/solver.cpp)
