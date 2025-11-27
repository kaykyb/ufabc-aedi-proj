#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"

typedef struct cliente
{
    char *cpf;
    int idade;
    int anos_cnh;
    bool inadimplente;
    int acidentes;
    float gastos;
    int dias_alugados;
    ClienteCategoria categoria;

    FuncGetCategoria get_categoria;
} Cliente;

Cliente *cliente_cria(char *cpf, int idade, int anos_cnh, bool inadimplente, int acidentes, float gastos, int dias_alugados, FuncGetCategoria get_categoria)
{
    Cliente *c = malloc(sizeof(Cliente));
    if (c == NULL)
    {
        printf("Erro: Ocorreu uma falha ao alocar memória\n");
        exit(1);
    }

    if (strlen(cpf) > 11)
    {
        printf("Erro: Um CPF com mais de 11 digitos foi passado.");
        exit(1);
    }

    c->cpf = malloc(sizeof(char) * 12);
    strcpy(c->cpf, cpf);

    c->idade = idade;
    c->anos_cnh = anos_cnh;
    c->inadimplente = inadimplente;
    c->acidentes = acidentes;
    c->gastos = gastos;
    c->dias_alugados = dias_alugados;

    c->get_categoria = get_categoria;
    c->categoria = get_categoria(c);

    return c;
}

void cliente_libera(Cliente *c)
{
    free(c->cpf);
    free(c);
}

void cliente_atualiza_idade(Cliente *c, int idade)
{
    c->idade = idade;
    c->categoria = c->get_categoria(c);
}

void cliente_atualiza_anos_cnh(Cliente *c, int anos_cnh)
{
    c->anos_cnh = anos_cnh;
    c->categoria = c->get_categoria(c);
}

void cliente_atualiza_inadimplente(Cliente *c, bool inadimplente)
{
    c->inadimplente = inadimplente;
    c->categoria = c->get_categoria(c);
}

void cliente_atualiza_acidentes(Cliente *c, int acidentes)
{
    c->acidentes = acidentes;
    c->categoria = c->get_categoria(c);
}

void cliente_atualiza_gastos(Cliente *c, float gastos)
{
    c->gastos = gastos;
    c->categoria = c->get_categoria(c);
}

void cliente_atualiza_dias_alugados(Cliente *c, int dias_alugados)
{
    c->dias_alugados = dias_alugados;
    c->categoria = c->get_categoria(c);
}

char *cliente_cpf(Cliente *c)
{
    return c->cpf;
}

int cliente_idade(Cliente *c)
{
    return c->idade;
}

int cliente_anos_cnh(Cliente *c)
{
    return c->anos_cnh;
}

bool cliente_inadimplente(Cliente *c)
{
    return c->inadimplente;
}

int cliente_acidentes(Cliente *c)
{
    return c->acidentes;
}

float cliente_gastos(Cliente *c)
{
    return c->gastos;
}

int cliente_dias_alugados(Cliente *c)
{
    return c->dias_alugados;
}

int cliente_categoria(Cliente *c)
{
    return c->categoria;
}
