#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

struct avl_no
{
    struct avl_no *esq;
    struct avl_no *dir;
    void *info;
    int altura;
};

struct avl
{
    FuncComparar comparar;
    FuncGetIdentidade get_identidade;
    FuncLiberarInfo liberar_info;
    struct avl_no *topo;
};

AVL *avl_criar(FuncComparar comparar, FuncGetIdentidade get_identidade, FuncLiberarInfo liberar_info)
{
    if (comparar == NULL || get_identidade == NULL || liberar_info == NULL)
    {
        printf("As FuncComparar, FuncGetIdentidade e FuncLiberarInfo não podem ser nulas\n");
        exit(1);
    }

    AVL *avl = malloc(sizeof(AVL));
    if (avl == NULL)
    {
        printf("Erro: Ocorreu uma falha ao alocar memória\n");
        exit(1);
    }

    avl->comparar = comparar;
    avl->get_identidade = get_identidade;
    avl->liberar_info = liberar_info;
    avl->topo = NULL;

    return avl;
}

static int avl_altura(struct avl_no *no)
{
    if (no == NULL)
        return -1;

    return no->altura;
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static struct avl_no *avl_rotacao_direita(struct avl_no *y)
{
    struct avl_no *x = y->esq;
    struct avl_no *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(avl_altura(y->esq), avl_altura(y->dir)) + 1;
    x->altura = max(avl_altura(x->esq), avl_altura(x->dir)) + 1;

    return x;
}

static struct avl_no *avl_rotacao_esquerda(struct avl_no *x)
{
    struct avl_no *y = x->dir;
    struct avl_no *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(avl_altura(x->esq), avl_altura(x->dir)) + 1;
    y->altura = max(avl_altura(y->esq), avl_altura(y->dir)) + 1;

    return y;
}

// --- BALANCEAMENTO---
int avl_balanceamento(struct avl_no *no)
{
    return avl_altura(no->esq) - avl_altura(no->dir);
}

struct avl_no *avl_balancear(struct avl_no *no)
{
    if (no == NULL)
        return NULL;

    no->altura = 1 + max(avl_altura(no->esq), avl_altura(no->dir));
    int balanceamento = avl_balanceamento(no);

    if (balanceamento > 1)
    {

        if (avl_balanceamento(no->esq) < 0)
        {
            no->esq = avl_rotacao_esquerda(no->esq);
        }

        return avl_rotacao_direita(no);
    }

    if (balanceamento < -1)
    {

        if (avl_balanceamento(no->dir) > 0)
        {
            no->dir = avl_rotacao_direita(no->dir);
        }

        return avl_rotacao_esquerda(no);
    }

    return no;
}

// --- INSERÇÃO ---
static struct avl_no *avl_inserir_recursiva(struct avl_no *no, void *elem, FuncComparar comparar, FuncGetIdentidade get_identidade)
{
    if (no == NULL)
    {
        struct avl_no *avl = malloc(sizeof(struct avl_no));
        if (!avl)
        {
            printf("Erro: Ocorreu uma falha ao alocar memória\n");
            exit(1);
        }

        avl->info = elem;
        avl->esq = NULL;
        avl->dir = NULL;
        avl->altura = 0;

        return avl;
    }

    void *identidade_no = get_identidade(no->info);
    void *identidade_elem = get_identidade(elem);

    int comp = comparar(identidade_elem, identidade_no);

    free(identidade_no);
    free(identidade_elem);

    if (comp < 0)
    {
        no->esq = avl_inserir_recursiva(no->esq, elem, comparar, get_identidade);
    }
    else if (comp > 0)
    {
        no->dir = avl_inserir_recursiva(no->dir, elem, comparar, get_identidade);
    }
    else
    {
        return no;
    }

    return avl_balancear(no);
}

void avl_inserir(AVL *avl, void *elem)
{
    avl->topo = avl_inserir_recursiva(avl->topo, elem, avl->comparar, avl->get_identidade);
}

void *avl_buscar(AVL *avl, void *identidade)
{
    struct avl_no *topo = avl->topo;
    void *identidade_topo;
    int comp;

    while (topo)
    {
        identidade_topo = avl->get_identidade(topo->info);
        comp = avl->comparar(identidade, identidade_topo);
        free(identidade_topo);

        if (comp == 0)
        {
            return topo->info;
        }

        if (comp < 0)
        {
            topo = topo->esq;
        }
        else
        {
            topo = topo->dir;
        }
    }

    return NULL;
}

// --- LIBERAÇÃO ---
static void avl_liberar_recursiva(struct avl_no *no, FuncLiberarInfo liberar_info)
{
    if (no == NULL)
        return;

    avl_liberar_recursiva(no->esq, liberar_info);
    avl_liberar_recursiva(no->dir, liberar_info);

    liberar_info(no->info);
    free(no);
}

void avl_liberar(AVL *avl)
{
    if (avl == NULL)
        return;

    avl_liberar_recursiva(avl->topo, avl->liberar_info);
    free(avl);
}

// --- Representação em Texto ---
static void avl_representacao_string_recursiva(struct avl_no *no, char *buffer, FuncGetIdentidade get_identidade)
{
    if (no == NULL)
    {
        strcat(buffer, "<>");
        return;
    }

    strcat(buffer, "<");

    char *str_valor = get_identidade(no->info);
    if (str_valor != NULL)
    {
        strcat(buffer, str_valor);
        free(str_valor);
    }

    strcat(buffer, " ");
    avl_representacao_string_recursiva(no->esq, buffer, get_identidade);

    strcat(buffer, " ");
    avl_representacao_string_recursiva(no->dir, buffer, get_identidade);

    strcat(buffer, ">");
}

char *avl_representacao_string(AVL *avl)
{
    char *s = malloc(sizeof(char) * 512);
    if (s == NULL)
    {
        printf("Erro: Ocorreu uma falha ao alocar memória\n");
        exit(1);
    }

    s[0] = '\0';

    if (avl)
        avl_representacao_string_recursiva(avl->topo, s, avl->get_identidade);

    return s;
}
