add_executable(
    stack_cpp
    main.cpp
)

target_compile_options(
    stack_cpp
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c++11
)

target_include_directories(
    stack_cpp
    PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
)

target_link_libraries(
    stack_cpp
    PRIVATE
    -lcstack
)    
