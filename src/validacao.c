#include <stdbool.h>

bool valida_cpf(char *cpf)
{
    for (int i = 0; i < 11; i++)
        if (cpf[i] < '0' || cpf[i] > '9')
            return false;

    return true;
}

bool valida_idade(int idade)
{
    return idade >= 18 && idade <= 120;
}

bool valida_anos_cnh(int anos_cnh, int idade)
{
    return anos_cnh >= 0 && anos_cnh <= (idade - 18);
}

bool valida_inadimplente(int inadimplente)
{
    return inadimplente == 0 || inadimplente == 1;
}

bool valida_acidentes(int acidentes)
{
    return acidentes >= 0;
}

bool valida_gastos(float gastos)
{
    return gastos >= 0;
}

bool valida_dias_alugados(int dias)
{
    return dias >= 0 && dias <= 366;
}
