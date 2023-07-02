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
    test_libcstack
    test_cstack.c
)

target_compile_options(
    test_libcstack
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
    -g
)

target_link_libraries(
    test_libcstack
    PRIVATE
    -lcstack
)
