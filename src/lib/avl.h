#ifndef UFABC_AEDI_PROJ_AVL_H
#define UFABC_AEDI_PROJ_AVL_H

typedef int (*FuncComparar)(void *, void *);
typedef void *(*FuncGetIdentidade)(void *);
typedef void (*FuncLiberarInfo)(void *);

typedef struct avl AVL;

AVL *avl_criar(FuncComparar comparar, FuncGetIdentidade get_identidade, FuncLiberarInfo liberar_info);
void avl_liberar(AVL *avl);

void avl_inserir(AVL *avl, void *elem);
void *avl_buscar(AVL *avl, void *identidade);

char *avl_representacao_string(AVL *avl);

#endif
