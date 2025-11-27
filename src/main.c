#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/avl.h"
#include "lib/cliente.h"
#include "lib/decisao.h"

// Armazenamento de Clientes
static AVL *avl;
static Decisao *decisao;

int func_compara(void *pa, void *pb)
{
    char *a = (char *)pa;
    char *b = (char *)pb;
    return strcmp(a, b);
}

void *func_get_identidade(void *elem)
{
    return cliente_cpf(elem);
}

void func_libera(void *elem)
{
    cliente_libera(elem);
}

int func_get_categoria(Cliente *c)
{
    return *(int *)decisao_classificar(decisao, c);
}

// Helpers
void clear(void)
{
    printf("\033[2J\033[H");
}

void limpar_buffer_entrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void header(char *titulo)
{
    printf("=================================================\n");
    printf("                     UFABCars\n");
    printf("=================================================\n");
    printf(" %s\n", titulo);
    printf("=================================================\n");
}

void menu(void);

void stop_pressione_continuar()
{
    printf("\n---------------------------------------------------------\n");
    printf("Pressione qualquer tecla para voltar ao menu principal...");
    getchar();
}

bool checa_cpf_valido(char *cpf)
{
    for (int i = 0; i < 11; i++)
        if (cpf[i] < '0' || cpf[i] > '9')
            return false;

    return true;
}

// Interface
void visualizar_cliente(Cliente *c)
{
    clear();
    header("Visualizar Cliente");

    printf("CPF:                  %s\n", cliente_cpf(c));
    printf("Categoria do Cliente: %d\n", cliente_categoria(c));

    stop_pressione_continuar();
    menu();
}

void adicionar_cliente()
{
    clear();
    header("Adicionar Cliente");
    printf("Insira os dados do Cliente:\n\n");

    char cpf[12];
    printf("CPF (Apenas numeros): ");
    fgets(cpf, 12, stdin);
    limpar_buffer_entrada();

    if (!checa_cpf_valido(cpf))
    {
        printf("Erro: CPF invalido.\n");
        stop_pressione_continuar();
    }

    if (avl_buscar(avl, cpf))
    {
        printf("Erro: Cliente ja existe no banco de dados...");
        stop_pressione_continuar();
    };

    int idade;
    printf("Idade: ");
    scanf("%d", &idade);

    int anos_cnh;
    printf("Anos de CNH permanente: ");
    scanf("%d", &anos_cnh);

    int inadimplente;
    printf("O cliente esta inadimplente? (1 para sim, 0 para nao): ");
    scanf("%d", &inadimplente);

    if (inadimplente < 0 || inadimplente > 1)
    {
        printf("Erro: Inadimplente deve ser '0' ou '1'...");
        stop_pressione_continuar();
    }

    int acidentes;
    printf("Numero de acidentes causados: ");
    scanf("%d", &acidentes);

    float gastos;
    printf("Gastos na loja neste ano: ");
    scanf("%f", &gastos);

    int dias_alugados;
    printf("Dias de aluguel neste ano: ");
    scanf("%d", &dias_alugados);
    getchar();

    Cliente *c = cliente_cria(cpf, idade, anos_cnh, inadimplente, acidentes, gastos, dias_alugados, func_get_categoria);
    avl_inserir(avl, c);

    visualizar_cliente(c);
}

void buscar_cliente()
{
    clear();
    header("Buscar Cliente");
    printf("Buscar um cliente por CPF.\n\n");

    char cpf[12];
    printf("CPF (Apenas numeros): ");
    fgets(cpf, 12, stdin);
    limpar_buffer_entrada();

    if (!checa_cpf_valido(cpf))
    {
        printf("Erro: CPF invalido.\n");
        stop_pressione_continuar();
    }

    Cliente *c = avl_buscar(avl, cpf);
    if (!c)
    {
        printf("Erro: Cliente nao existe no banco de dados.");
        stop_pressione_continuar();
    };

    visualizar_cliente(c);
}

void menu(void)
{

    clear();
    printf("=================================================\n");
    printf("                     UFABCars\n");
    printf("=================================================\n");
    printf("Bem-vindo ao Sistema de Gerenciamento de Clientes\n");
    printf("\n");
    printf("    MENU\n");
    printf("[1] Adicionar Cliente\n");
    printf("[2] Buscar Cliente\n");
    printf("\n");
    printf("Digite o Número da Opção: ");

    int op;
    scanf("%d", &op);
    getchar();

    if (op == 1)
    {
        adicionar_cliente();
        return;
    }

    if (op == 2)
    {
        buscar_cliente();
        return;
    }

    menu();
}

// Funcoes de verificacao
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

int main(void)
{
    avl = avl_criar(func_compara, func_get_identidade, func_libera);

    // Resultados possiveis
    int valor_bloqueado = 0;
    Decisao *resultado_bloqueado = decisao_criar_resultado(&valor_bloqueado);

    int valor_inativo = 1;
    Decisao *resultado_inativo = decisao_criar_resultado(&valor_inativo);

    int valor_standard = 2;
    Decisao *resultado_standard = decisao_criar_resultado(&valor_standard);

    int valor_gold = 3;
    Decisao *resultado_gold = decisao_criar_resultado(&valor_gold);

    int valor_platinum = 4;
    Decisao *resultado_platinum = decisao_criar_resultado(&valor_platinum);

    int valor_elite = 5;
    Decisao *resultado_elite = decisao_criar_resultado(&valor_elite);

    int valor_risco_moderado = 6;
    Decisao *resultado_risco_moderado = decisao_criar_resultado(&valor_risco_moderado);

    int valor_alto_risco = 7;
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

    menu();
    return 0;
}
