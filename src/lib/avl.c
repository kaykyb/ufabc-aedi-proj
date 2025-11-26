#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

struct avl_no {
    struct avl_no* esq;
    struct avl_no* dir;
    void* info;
    int altura;
};

struct avl {
    FuncComparacao comparador;
    FuncIdentidade identidade;
    FuncLiberarInfo liberar_info;
    struct avl_no* topo;
};

AVL *avl_criar(FuncComparacao comparador, FuncIdentidade identidade, FuncLiberarInfo liberar_info)
{
    AVL* avl = malloc(sizeof(AVL));
    if (avl) {
        avl->comparador = comparador;
        avl->identidade = identidade;
        avl->liberar_info = liberar_info;

        avl->topo = NULL;
    }
    return avl;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int avl_altura(struct avl_no* no) {
    if (no == NULL) return 0;
    return no->altura;
}

struct avl_no* avl_rotacao_direita(struct avl_no* y) {
    struct avl_no* x = y->esq;
    struct avl_no* T2 = x->dir;
    
    x->dir = y;
    y->esq = T2;

    y->altura = max(avl_altura(y->esq), avl_altura(y->dir)) + 1;
    x->altura = max(avl_altura(x->esq), avl_altura(x->dir)) + 1;

    return x;
}

struct avl_no* avl_rotacao_esquerda(struct avl_no* x) {
    struct avl_no* y = x->dir;
    struct avl_no* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(avl_altura(x->esq), avl_altura(x->dir)) + 1;
    y->altura = max(avl_altura(y->esq), avl_altura(y->dir)) + 1;

    return y;
}

// --- BALANCEAMENTO---

int avl_balanceamento(struct avl_no* no) {
    if (no == NULL) return 0;
    return avl_altura(no->esq) - avl_altura(no->dir);
}

struct avl_no* avl_balancear(struct avl_no* no) {
    if (no == NULL) return NULL;
    
    no->altura = 1 + max(avl_altura(no->esq), avl_altura(no->dir));

    int balance = avl_balanceamento(no);

    if (balance > 1) {

        if (avl_balanceamento(no->esq) < 0) {
              no->esq = avl_rotacao_esquerda(no->esq);
        }

        return avl_rotacao_direita(no);
    }

    if (balance < -1) {

        if (avl_balanceamento(no->dir) > 0) {
              no->dir = avl_rotacao_direita(no->dir);
        }

        return avl_rotacao_esquerda(no);
    }

    return no;
}

// --- INSERÇÃO ---

struct avl_no * avl_inserir_recursiva(struct avl_no *no, void *elem, FuncComparacao comparador, FuncIdentidade identidade) {
    if (!no) {
        struct avl_no* avl = malloc(sizeof(struct avl_no));
        avl->info = elem;
        avl->esq = NULL;
        avl->dir = NULL;
        avl->altura = 1;

        return avl;
    }

    void* identidade_no = identidade(no->info);
    void* identidade_elem = identidade(elem);

    int comp = comparador(identidade_elem, identidade_no);

    free(identidade_no);
    free(identidade_elem);

    if (comp < 0) {
        no->esq = avl_inserir_recursiva(no->esq, elem, comparador, identidade);
    } else if (comp > 0) {
        no->dir = avl_inserir_recursiva(no->dir, elem, comparador, identidade);
    }else {
        return no;
    }

    return avl_balancear(no);
}

void avl_inserir(AVL *avl, void *elem)
{
    avl->topo = avl_inserir_recursiva(avl->topo, elem, avl->comparador, avl->identidade);
}

void *avl_buscar(AVL *avl, void *identidade)
{
    struct avl_no* topo = avl->topo;
    void* identidade_topo;
    int comp;

    while (topo) {
        identidade_topo = avl->identidade(topo->info);
        comp = avl->comparador(identidade, identidade_topo);
        free(identidade_topo);

        if (comp == 0) {
            return topo->info;
        } else if(comp < 0) {
            topo = topo->esq;
        } else {
            topo = topo->dir;
        }
    }

    return NULL;
}

void _montar_string_recursiva(struct avl_no* no, char* buffer, FuncIdentidade identidade) {
    if (no == NULL) {
        strcat(buffer, "<>");
        return;
    }

    strcat(buffer, "<");
    char* str_valor = identidade(no->info);
    if (str_valor) {
        strcat(buffer, str_valor);
        free(str_valor);
    }

    strcat(buffer, " ");
    _montar_string_recursiva(no->esq, buffer, identidade);

    strcat(buffer, " ");
    _montar_string_recursiva(no->dir, buffer, identidade);

    strcat(buffer, ">");
}

char *internal_avl_representacao_string(AVL *avl)
{
    char *s = malloc(sizeof(char) * 512);
    if (s == NULL) return NULL;

    s[0] = '\0';
    if (avl)
        _montar_string_recursiva(avl->topo, s, avl->identidade);

    return s;
}

// --- LIBERAÇÃO ---

void avl_liberar_recursiva(struct avl_no *no, FuncLiberarInfo liberar_info) {
    if (no == NULL) return ;

    avl_liberar_recursiva(no->esq, liberar_info);
    avl_liberar_recursiva(no->dir, liberar_info);

    if (liberar_info && no->info) {
        liberar_info(no->info);
    }
    free(no);
}

void avl_liberar(AVL *avl)
{
    if (avl == NULL) return;
    avl_liberar_recursiva(avl->topo, avl->liberar_info);
    free(avl);
}


