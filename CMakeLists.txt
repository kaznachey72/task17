cmake_minimum_required(VERSION 3.10)
project(ex17-cstack)

#--- cstack ------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/cstack)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/cstack)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/client_cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/client_py)
