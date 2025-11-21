cmake_minimum_required(VERSION 3.5)
project(ufabc_aedi_proj C)

set(CMAKE_C_STANDARD 11)

add_library(ufabc_aedi_proj_lib
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

add_executable(run_cliente_tests test/cliente_test.c)
target_link_libraries(run_cliente_tests PRIVATE ufabc_aedi_proj_lib)

add_test(NAME cliente_teste_criacao               COMMAND run_tests criacao)
add_test(NAME cliente_teste_atualiza_idade        COMMAND run_tests idade)
add_test(NAME cliente_teste_atualiza_cnh          COMMAND run_tests cnh)
add_test(NAME cliente_teste_atualiza_inadimplente COMMAND run_tests inadimplencia)
add_test(NAME cliente_teste_atualiza_acidentes    COMMAND run_tests acidentes)
add_test(NAME cliente_teste_atualiza_gastos       COMMAND run_tests gastos)
add_test(NAME cliente_teste_atualiza_dias         COMMAND run_tests dias)
