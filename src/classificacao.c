#include "lib/cliente.h"
#include "lib/decisao.h"

static Decisao *decisao;
static int valor_bloqueado = 0;
static int valor_inativo = 1;
static int valor_standard = 2;
static int valor_gold = 3;
static int valor_platinum = 4;
static int valor_elite = 5;
static int valor_risco_moderado = 6;
static int valor_alto_risco = 7;

// Classificadores
bool verifica_elite(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_gastos(c) > 500000;
}

bool verifica_inadimplente(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_inadimplente(c);
}

bool verifica_acidentes(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_acidentes(c) > 0;
}

bool verifica_idade(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_idade(c) > 25;
}

bool verifica_gasto_anual(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_gastos(c) > 10000;
}

bool verifica_anos_cnh(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_anos_cnh(c) > 5;
}

bool verifica_alugou(void *elem)
{
    Cliente *c = (Cliente *)elem;
    return cliente_dias_alugados(c) > 0;
}

void classificacao_inicializar()
{
    Decisao *resultado_bloqueado = decisao_criar_resultado(&valor_bloqueado);
    Decisao *resultado_inativo = decisao_criar_resultado(&valor_inativo);
    Decisao *resultado_standard = decisao_criar_resultado(&valor_standard);
    Decisao *resultado_gold = decisao_criar_resultado(&valor_gold);
    Decisao *resultado_platinum = decisao_criar_resultado(&valor_platinum);
    Decisao *resultado_elite = decisao_criar_resultado(&valor_elite);
    Decisao *resultado_risco_moderado = decisao_criar_resultado(&valor_risco_moderado);
    Decisao *resultado_alto_risco = decisao_criar_resultado(&valor_alto_risco);

    decisao = decisao_criar_verificador(
        verifica_elite,
        decisao_criar_verificador(
            verifica_inadimplente,
            decisao_criar_verificador(
                verifica_acidentes,
                decisao_criar_verificador(
                    verifica_gasto_anual,
                    decisao_criar_verificador(verifica_alugou, resultado_inativo, resultado_standard),
                    decisao_criar_verificador(verifica_anos_cnh, resultado_gold, resultado_platinum)),
                decisao_criar_verificador(verifica_idade, resultado_alto_risco, resultado_risco_moderado)),
            resultado_bloqueado),
        resultado_elite);
}

ClienteCategoria classificacao_get_categoria(Cliente *c)
{
    return *(int *)decisao_classificar(decisao, c);
}

void classificacao_liberar()
{
    decisao_liberar(decisao);
}
