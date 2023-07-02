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
    libcmatrix_test
    test_cmatrix.c
)

target_compile_options(
    libcmatrix_test
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -std=c11
    -g
)

target_link_libraries(
    libcmatrix_test
    PRIVATE
    -lcmatrix
)
