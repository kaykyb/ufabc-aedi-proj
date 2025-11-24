#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

struct avl_no {
    struct avl_no* esq;
    struct avl_no* dir;
    void* info;
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
    avl->comparador = comparador;
    avl->identidade = identidade;
    avl->liberar_info = liberar_info;

    return avl;
}

void avl_liberar(AVL *avl)
{

}

struct avl_no * avl_inserir_recursiva(struct avl_no *topo, void *elem, FuncComparacao comparador, FuncIdentidade identidade) {
    if (!topo) {
        struct avl_no* avl = malloc(sizeof(struct avl_no));
        avl->info = elem;
        return avl;
    }

    void* identidade_topo = identidade(topo->info);
    void* identidade_elem = identidade(elem);

    int comp = comparador(identidade_elem, identidade_topo);
    free(identidade_topo);
    free(identidade_elem);

    if (comp < 0) {
        topo->esq = avl_inserir_recursiva(topo->esq, elem, comparador, identidade);
    } else if (comp > 0) {
        topo->dir = avl_inserir_recursiva(topo->dir, elem, comparador, identidade);
    }

    return topo;
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
        }

        if (comp == -1) {
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

    _montar_string_recursiva(avl->topo, s, avl->identidade);

    return s;
}
