#ifndef UFABC_AEDI_PROJ_DECISAO_H
#define UFABC_AEDI_PROJ_DECISAO_H
#include <stdbool.h>

typedef bool (*FuncVerificador)(void*);

typedef struct decisao Decisao;

Decisao* decisao_criar_verificador(FuncVerificador func, Decisao* falso, Decisao* verdadeiro);
Decisao* decisao_criar_resultado(void* resultado);
void decisao_liberar(Decisao*);

void* decisao_classificar(void* entidade);

#endif
