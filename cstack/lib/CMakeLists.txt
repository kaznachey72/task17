#--- lib ---------------------

add_library(
    cstack 
    SHARED
    cstack.c
)

target_compile_options(
    cstack 
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
)

#--- test --------------------

add_executable(
    test_lib
    test_cstack.c
)

target_compile_options(
    test_lib
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
    -g
)

target_link_libraries(
    test_lib
    PRIVATE
    -lcstack
)
