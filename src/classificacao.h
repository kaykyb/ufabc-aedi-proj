#ifndef UFABC_AEDI_PROJ_CLASSIFICACAO_H
#define UFABC_AEDI_PROJ_CLASSIFICACAO_H

#include "lib/cliente.h"

void classificacao_inicializar();
ClienteCategoria classificacao_get_categoria(Cliente *c);
void classificacao_liberar();

#endif