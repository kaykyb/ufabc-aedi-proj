#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

AVL *avl_criar(FuncComparacao comparador, FuncIdentidade identidade, FuncLiberarInfo liberar_info)
{
    return NULL;
}

void avl_liberar(AVL *avl)
{
}

void avl_inserir(AVL *avl, void *elem)
{
}

void *avl_buscar(AVL *avl, void *identidade)
{
    return NULL;
}

char *internal_avl_representacao_string(AVL *avl)
{
    char *s = malloc(sizeof(char) * 20);
    strcpy(s, "<>");
    return s;
}
