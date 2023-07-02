#--- lib ---------------------

add_library(
    cmatrix
    SHARED
    cmatrix.c
)

target_compile_options(
    cmatrix
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
)

#--- test --------------------

add_executable(
    test_libcmatrix
    test_cmatrix.c
)

target_compile_options(
    test_libcmatrix
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
    -g
)

target_link_libraries(
    test_libcmatrix
    PRIVATE
    -lcmatrix
)
