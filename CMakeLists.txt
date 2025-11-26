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

# Cliente
add_executable(run_cliente_tests test/cliente_test.c)
target_link_libraries(run_cliente_tests PRIVATE ufabc_aedi_proj_lib)

add_test(NAME cliente_teste_criacao               COMMAND run_cliente_tests criacao)
add_test(NAME cliente_teste_atualiza_idade        COMMAND run_cliente_tests idade)
add_test(NAME cliente_teste_atualiza_cnh          COMMAND run_cliente_tests cnh)
add_test(NAME cliente_teste_atualiza_inadimplente COMMAND run_cliente_tests inadimplencia)
add_test(NAME cliente_teste_atualiza_acidentes    COMMAND run_cliente_tests acidentes)
add_test(NAME cliente_teste_atualiza_gastos       COMMAND run_cliente_tests gastos)
add_test(NAME cliente_teste_atualiza_dias         COMMAND run_cliente_tests dias)

# AVL
add_executable(run_avl_tests test/avl_test.c)
target_link_libraries(run_avl_tests PRIVATE ufabc_aedi_proj_lib)

add_test(NAME avl_vazia       COMMAND run_avl_tests criacao)
add_test(NAME avl_insert1     COMMAND run_avl_tests simples)
add_test(NAME avl_insert3     COMMAND run_avl_tests multipla)
add_test(NAME avl_rotacao_dir COMMAND run_avl_tests rot_dir)
add_test(NAME avl_rotacao_esq COMMAND run_avl_tests rot_esq)
add_test(NAME avl_rotacao_lr  COMMAND run_avl_tests rot_lr)
add_test(NAME avl_rotacao_rl  COMMAND run_avl_tests rot_rl)
add_test(NAME avl_busca       COMMAND run_avl_tests busca)

# Decisao
add_executable(run_decisao_tests test/decisao_test.c)
target_link_libraries(run_decisao_tests PRIVATE ufabc_aedi_proj_lib)

add_test(NAME decisao_folha      COMMAND run_decisao_tests folha)
add_test(NAME decisao_simples    COMMAND run_decisao_tests simples)
add_test(NAME decisao_complexa   COMMAND run_decisao_tests complexa)
