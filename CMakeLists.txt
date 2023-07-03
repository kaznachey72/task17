cmake_minimum_required(VERSION 3.10)
project(ex17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#--- cstack ------------------

add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/client_cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/cstack/client_py)

#--- cmatrix -----------------

add_subdirectory(${CMAKE_SOURCE_DIR}/cmatrix/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/cmatrix/client_cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/cmatrix/client_py)
