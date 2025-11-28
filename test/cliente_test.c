#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../src/lib/cliente.h"

static int categoria = 0;
ClienteCategoria func_categoria(Cliente *c)
{
    categoria++;
    return categoria;
}

Cliente *setup_cliente()
{
    categoria = 0;
    return cliente_cria("ABC", 12, 2, true, 5, 234.3f, 42, func_categoria);
}

void teste_criacao()
{
    Cliente *c = setup_cliente();
    assert(strcmp(cliente_cpf(c), "ABC") == 0);
    assert(cliente_idade(c) == 12);
    assert(cliente_anos_cnh(c) == 2);
    assert(cliente_inadimplente(c) == true);
    assert(cliente_acidentes(c) == 5);
    assert(cliente_gastos(c) == 234.3f);
    assert(cliente_dias_alugados(c) == 42);

    assert(cliente_categoria(c) == 1);

    cliente_libera(c);
}

void teste_atualiza_idade()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_idade(c, 43);

    assert(cliente_idade(c) == 43);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

void teste_atualiza_cnh()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_anos_cnh(c, 6);

    assert(cliente_anos_cnh(c) == 6);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

void teste_atualiza_inadimplencia()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_inadimplente(c, false);

    assert(cliente_inadimplente(c) == false);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

void teste_atualiza_acidentes()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_acidentes(c, 8);

    assert(cliente_acidentes(c) == 8);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

void teste_atualiza_gastos()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_gastos(c, 23.0f);

    assert(cliente_gastos(c) == 23.0f);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

void teste_atualiza_dias()
{
    Cliente *c = setup_cliente();
    cliente_atualiza_dias_alugados(c, 9);

    assert(cliente_dias_alugados(c) == 9);
    assert(cliente_categoria(c) == 2);

    cliente_libera(c);
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "criacao") == 0)
        teste_criacao();
    else if (strcmp(argv[1], "idade") == 0)
        teste_atualiza_idade();
    else if (strcmp(argv[1], "cnh") == 0)
        teste_atualiza_cnh();
    else if (strcmp(argv[1], "inadimplencia") == 0)
        teste_atualiza_inadimplencia();
    else if (strcmp(argv[1], "acidentes") == 0)
        teste_atualiza_acidentes();
    else if (strcmp(argv[1], "gastos") == 0)
        teste_atualiza_gastos();
    else if (strcmp(argv[1], "dias") == 0)
        teste_atualiza_dias();
    else
    {
        printf("Teste desconhecido: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
