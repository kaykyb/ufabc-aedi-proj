#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../src/lib/decisao.h"

typedef struct
{
    int score_credito;
    bool tem_dividas;
} Cliente;

bool verifica_score_alto(void *i)
{
    Cliente *c = (Cliente *)i;
    return c->score_credito > 700;
}

bool verifica_score_medio(void *i)
{
    Cliente *c = (Cliente *)i;
    return c->score_credito > 500;
}

bool verifica_sem_dividas(void *i)
{
    Cliente *c = (Cliente *)i;
    return c->tem_dividas == false;
}

void teste_folha_unica()
{
    char *res_aprovado = "APROVADO";
    Decisao *arvore = decisao_criar_resultado(res_aprovado);

    Cliente c = {0, true};
    assert(decisao_classificar(arvore, &c) == res_aprovado);

    decisao_liberar(arvore);
}

void teste_decisao_simples()
{
    char *res_aprovado = "APROVADO";
    char *res_reprovado = "REPROVADO";

    Decisao *no_true = decisao_criar_resultado(res_aprovado);
    Decisao *no_false = decisao_criar_resultado(res_reprovado);

    Decisao *raiz = decisao_criar_verificador(verifica_score_alto, no_false, no_true);

    Cliente c1 = {.score_credito = 800};
    assert(decisao_classificar(raiz, &c1) == res_aprovado);

    Cliente c2 = {.score_credito = 600};
    assert(decisao_classificar(raiz, &c2) == res_reprovado);

    decisao_liberar(raiz);
}

void teste_decisao_complexa()
{
    Decisao *r_sim = decisao_criar_resultado("SIM");
    Decisao *r_nao = decisao_criar_resultado("NAO");

    Decisao *checa_divida = decisao_criar_verificador(verifica_sem_dividas, r_nao, r_sim);

    Decisao *r_nao_score = decisao_criar_resultado("NAO");
    Decisao *raiz = decisao_criar_verificador(verifica_score_medio, r_nao_score, checa_divida);

    Cliente c1 = {600, false};
    Cliente c2 = {600, true};
    Cliente c3 = {400, false};

    assert(strcmp(decisao_classificar(raiz, &c1), "SIM") == 0);
    assert(strcmp(decisao_classificar(raiz, &c2), "NAO") == 0);
    assert(strcmp(decisao_classificar(raiz, &c3), "NAO") == 0);

    decisao_liberar(raiz);
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "folha") == 0)
        teste_folha_unica();
    else if (strcmp(argv[1], "simples") == 0)
        teste_decisao_simples();
    else if (strcmp(argv[1], "complexa") == 0)
        teste_decisao_complexa();
    else
    {
        printf("Teste desconhecido: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
