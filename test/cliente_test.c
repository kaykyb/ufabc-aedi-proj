#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "../src/lib/cliente.h"

static int categoria = 0;
int func_categoria(Cliente* c) {
    categoria++;
    return categoria;
}

int main() {
    // Consegue criar um cliente
    Cliente* c = cliente_cria("ABC", 12, 2, true, 5, 234.3f, 42, func_categoria);
    assert(strcmp(cliente_cpf(c), "ABC") == 0);
    assert(cliente_idade(c) == 12);
    assert(cliente_anos_cnh(c) == 2);
    assert(cliente_inadimplente(c) == true);
    assert(cliente_acidentes(c) == 5);
    assert(cliente_gastos(c) == 234.3f);
    assert(cliente_dias_alugados(c) == 42);

    // Cliente criado tem categoria adicionada
    assert(cliente_categoria(c) == 1);

    // Ao atualizar campos, a categoria é atualizada tambem
    cliente_atualiza_idade(c, 43);
    assert(cliente_idade(c) == 43);
    assert(cliente_categoria(c) == 2);

    cliente_atualiza_anos_cnh(c, 6);
    assert(cliente_anos_cnh(c) == 6);
    assert(cliente_categoria(c) == 3);

    cliente_atualiza_inadimplente(c, true);
    assert(cliente_inadimplente(c) == true);
    assert(cliente_categoria(c) == 4);

    cliente_atualiza_acidentes(c, 8);
    assert(cliente_acidentes(c) == 8);
    assert(cliente_categoria(c) == 5);

    cliente_atualiza_gastos(c, 23.0f);
    assert(cliente_gastos(c) == 23.0f);
    assert(cliente_categoria(c) == 6);

    cliente_atualiza_dias_alugados(c, 9);
    assert(cliente_dias_alugados(c) == 9);
    assert(cliente_categoria(c) == 7);

    // Consegue liberar cliente
    cliente_libera(c);

    return 0;
}
