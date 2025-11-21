#ifndef UFABC_AEDI_PROJ_AVL_H
#define UFABC_AEDI_PROJ_AVL_H
#include <stdbool.h>

typedef bool (*FuncComparacao)(void*, void*);
typedef char* (*FuncIdentidade)(void*);

typedef struct avl AVL;

AVL* avl_criar(FuncComparacao comparador, FuncIdentidade identidade);
void avl_liberar(AVL* avl);

void avl_inserir(AVL* avl, void* elem);
void* avl_buscar(AVL* avl);

char* avl_representacao_string(AVL* avl);

#endif //UFABC_AEDI_PROJ_AVL_H