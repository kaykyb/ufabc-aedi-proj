#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../src/lib/avl.h"

typedef struct
{
    int valor;
} Item;

Item *cria_item(int v)
{
    Item *i = malloc(sizeof(Item));
    i->valor = v;
    return i;
}

int func_compara(void *pa, void *pb)
{
    char *a = (char *)pa;
    char *b = (char *)pb;
    return strcmp(a, b);
}

void *func_identidade(void *i)
{
    char *str = malloc(20);
    sprintf(str, "%d", ((Item *)i)->valor);
    return str;
}

void func_libera(void *i)
{
    free(i);
}

void assert_estrutura(AVL *avl, char *esperado)
{
    char *real = avl_representacao_string(avl);
    if (strcmp(real, esperado) != 0)
    {
        fprintf(stderr, "ERRO ESTRUTURAL:\nEsperado: %s\nObtido: %s\n", esperado, real);
        free(real);
        abort();
    }
    free(real);
}

void teste_criacao_vazia()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);
    assert_estrutura(avl, "<>");

    avl_liberar(avl);
}

void teste_insercao_simples()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    Item *i1 = cria_item(10);
    avl_inserir(avl, i1);

    assert_estrutura(avl, "<10 <> <>>");
    avl_liberar(avl);
}

void teste_insercao_multipla()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    avl_inserir(avl, cria_item(2));
    avl_inserir(avl, cria_item(1));
    avl_inserir(avl, cria_item(3));

    assert_estrutura(avl, "<2 <1 <> <>> <3 <> <>>>");
    avl_liberar(avl);
}

void teste_balanceamento_rotacao_direita()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    avl_inserir(avl, cria_item(3));
    avl_inserir(avl, cria_item(2));
    avl_inserir(avl, cria_item(1));

    assert_estrutura(avl, "<2 <1 <> <>> <3 <> <>>>");
    avl_liberar(avl);
}

void teste_balanceamento_rotacao_esquerda()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    avl_inserir(avl, cria_item(1));
    avl_inserir(avl, cria_item(2));
    avl_inserir(avl, cria_item(3));

    assert_estrutura(avl, "<2 <1 <> <>> <3 <> <>>>");
    avl_liberar(avl);
}

void teste_busca()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);
    Item *i1 = cria_item(5);
    Item *i2 = cria_item(2);

    avl_inserir(avl, i1);
    avl_inserir(avl, i2);

    void *res1 = avl_buscar(avl, "2");
    assert(res1 != NULL);
    assert(((Item *)res1)->valor == 2);

    void *res2 = avl_buscar(avl, "8");
    assert(res2 == NULL);

    avl_liberar(avl);
}

void teste_balanceamento_rotacao_dupla_lr()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    avl_inserir(avl, cria_item(30));

    avl_inserir(avl, cria_item(10));

    avl_inserir(avl, cria_item(20));

    assert_estrutura(avl, "<20 <10 <> <>> <30 <> <>>>");

    avl_liberar(avl);
}

void teste_balanceamento_rotacao_dupla_rl()
{
    AVL *avl = avl_criar(func_compara, func_identidade, func_libera);

    avl_inserir(avl, cria_item(10));

    avl_inserir(avl, cria_item(30));

    avl_inserir(avl, cria_item(20));

    assert_estrutura(avl, "<20 <10 <> <>> <30 <> <>>>");

    avl_liberar(avl);
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "criacao") == 0)
        teste_criacao_vazia();
    else if (strcmp(argv[1], "simples") == 0)
        teste_insercao_simples();
    else if (strcmp(argv[1], "multipla") == 0)
        teste_insercao_multipla();
    else if (strcmp(argv[1], "rot_dir") == 0)
        teste_balanceamento_rotacao_direita();
    else if (strcmp(argv[1], "rot_esq") == 0)
        teste_balanceamento_rotacao_esquerda();
    else if (strcmp(argv[1], "busca") == 0)
        teste_busca();
    else if (strcmp(argv[1], "rot_lr") == 0)
        teste_balanceamento_rotacao_dupla_lr();
    else if (strcmp(argv[1], "rot_rl") == 0)
        teste_balanceamento_rotacao_dupla_rl();
    else
    {
        printf("Teste desconhecido: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
