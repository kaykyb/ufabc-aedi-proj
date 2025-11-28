#ifndef UFABC_AEDI_PROJ_ARMAZENAMENTO_H
#define UFABC_AEDI_PROJ_ARMAZENAMENTO_H

#include <stdbool.h>
#include "lib/cliente.h"
#include "classificacao.h"

void armazenamento_inicializar();
void armazenamento_liberar();
Cliente *armazenamento_criar_cliente(char *cpf, int idade, int anos_cnh, bool inadimplente, int acidentes, float gastos, int dias_alugados);
Cliente *armazenamento_buscar_cliente(char *cpf);

#endif
