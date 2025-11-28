#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/avl.h"
#include "lib/cliente.h"
#include "classificacao.h"

static AVL *avl;

static int comparar(void *pa, void *pb)
{
    char *a = (char *)pa;
    char *b = (char *)pb;
    return strcmp(a, b);
}

static void *get_identidade(void *elem)
{
    char *cpf_original = cliente_cpf(elem);
    char *cpf_copia = malloc(sizeof(char) * 12);
    strcpy(cpf_copia, cpf_original);
    return cpf_copia;
}

static void liberar(void *elem)
{
    cliente_libera(elem);
}

void armazenamento_inicializar()
{
    classificacao_inicializar();
    avl = avl_criar(comparar, get_identidade, liberar);
}

void armazenamento_liberar()
{
    classificacao_liberar();
    avl_liberar(avl);
}

Cliente *armazenamento_criar_cliente(char *cpf, int idade, int anos_cnh, bool inadimplente, int acidentes, float gastos, int dias_alugados)
{
    Cliente *c = cliente_cria(cpf, idade, anos_cnh, inadimplente, acidentes, gastos, dias_alugados, classificacao_get_categoria);
    avl_inserir(avl, c);

    return c;
}

Cliente *armazenamento_buscar_cliente(char *cpf)
{
    Cliente *c = avl_buscar(avl, cpf);
    return c;
}
