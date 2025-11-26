#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "decisao.h"

typedef enum
{
    VERIFICADOR,
    RESULTADO
} TipoNo;

struct decisao
{
    TipoNo tipo;

    FuncVerificar verificar;
    struct decisao *filho_falso;
    struct decisao *filho_verdadeiro;

    void *resultado;
};

Decisao *decisao_criar_verificador(FuncVerificar verificar, Decisao *falso, Decisao *verdadeiro)
{
    if (verificar == NULL)
    {
        printf("A FuncVerificador não pode ser NULL\n");
        exit(1);
    }

    Decisao *no = malloc(sizeof(Decisao));
    if (no == NULL)
    {
        printf("Erro: Ocorreu uma falha ao alocar memória\n");
        exit(1);
    }

    no->tipo = VERIFICADOR;
    no->verificar = verificar;
    no->filho_falso = falso;
    no->filho_verdadeiro = verdadeiro;

    return no;
}

Decisao *decisao_criar_resultado(void *resultado)
{
    Decisao *no = malloc(sizeof(Decisao));
    if (no == NULL)
    {
        printf("Falha ao alocar memória para nó resultado\n");
        exit(1);
    }

    no->tipo = RESULTADO;
    no->resultado = resultado;

    return no;
}

void decisao_liberar(Decisao *no)
{
    if (no == NULL)
        return;

    if (no->tipo == VERIFICADOR)
    {
        decisao_liberar(no->filho_falso);
        decisao_liberar(no->filho_verdadeiro);
    }

    free(no);
}

static void *decisao_classificar_recursivo(void *entidade, Decisao *no)
{
    if (no == NULL)
    {
        printf("Foi encontrado um Nó NULL durante a classificação e isso não está permitido\n");
        exit(1);
    }

    if (no->tipo == RESULTADO)
        return no->resultado;

    if (no->verificar(entidade))
        return decisao_classificar_recursivo(entidade, no->filho_verdadeiro);

    return decisao_classificar_recursivo(entidade, no->filho_falso);
}

void *decisao_classificar(Decisao *arvore, void *entidade)
{
    if (arvore == NULL)
    {
        printf("Árvore de decisão não pode ser NULL\n");
        exit(1);
    }

    if (entidade == NULL)
    {
        printf("Entidade não pode ser NULL\n");
        exit(1);
    }

    return decisao_classificar_recursivo(entidade, arvore);
}
