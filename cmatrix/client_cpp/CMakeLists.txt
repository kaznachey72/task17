add_executable(
    matrix_cpp
    main.cpp
    matrix.cpp
)

target_compile_options(
    matrix_cpp
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c++11
)

target_include_directories(
    matrix_cpp
    PRIVATE
    ${PROJECT_SOURCE_DIR}/cmatrix/lib
)

target_link_libraries(
    matrix_cpp
    PRIVATE
    -lcmatrix
)    
