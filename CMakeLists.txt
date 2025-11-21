cmake_minimum_required(VERSION 3.5)
project(ufabc_aedi_proj C)

set(CMAKE_C_STANDARD 11)

add_library(ufabc_aedi_proj_lib
        src/lib/example.c
        src/lib/example.h
        src/lib/cliente.c
        src/lib/cliente.h
        src/lib/decisao.c
        src/lib/decisao.h
        src/lib/avl.c
        src/lib/avl.h
)

add_executable(ufabc_aedi_proj src/main.c)
target_link_libraries(ufabc_aedi_proj PRIVATE ufabc_aedi_proj_lib)

enable_testing()
add_executable(run_tests test/example_test.c)
target_link_libraries(run_tests PRIVATE ufabc_aedi_proj_lib)

add_test(NAME example_test COMMAND run_tests)
