#ifndef UFABC_AEDI_PROJ_CLIENTE_H
#define UFABC_AEDI_PROJ_CLIENTE_H
#include <stdbool.h>

typedef struct cliente Cliente;

Cliente* cliente_cria(char* cpf, int idade, int anos_cnh, bool inadimplente, int acidentes, float gastos, int dias_alugados);
void cliente_libera(Cliente* c);

void cliente_atualiza_idade(Cliente* c, int idade);
void cliente_atualiza_anos_cnh(Cliente* c, int anos_cnh);
void cliente_atualiza_inadimplente(Cliente* c, bool inadimplente);
void cliente_atualiza_acidentes(Cliente* c, int acidentes);
void cliente_atualiza_gastos(Cliente* c, float gastos);
void cliente_atualiza_dias_alugados(Cliente* c, int dias_alugados);

char* cliente_cpf(Cliente* c);
int cliente_idade(Cliente* c);
int cliente_anos_cnh(Cliente* c);
bool cliente_inadimplente(Cliente* c);
int cliente_acidentes(Cliente* c);
float cliente_gastos(Cliente* c);
int cliente_dias_alugados(Cliente* c);
int cliente_categoria(Cliente* c);

#endif
