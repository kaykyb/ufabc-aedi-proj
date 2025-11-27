#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/avl.h"
#include "lib/cliente.h"
#include "classificacao.h"

// Armazenamento de Clientes
static AVL *avl;

int func_compara(void *pa, void *pb)
{
    char *a = (char *)pa;
    char *b = (char *)pb;
    return strcmp(a, b);
}

void *func_get_identidade(void *elem)
{
    char *cpf_original = cliente_cpf(elem);
    char *cpf_copia = malloc(sizeof(char) * 12);
    strcpy(cpf_copia, cpf_original);
    return cpf_copia;
}

void func_libera(void *elem)
{
    cliente_libera(elem);
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
        return;
    }

    if (avl_buscar(avl, cpf))
    {
        printf("Erro: Cliente ja existe no banco de dados...");
        stop_pressione_continuar();
        return;
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
        return;
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

    Cliente *c = cliente_cria(cpf, idade, anos_cnh, inadimplente, acidentes, gastos, dias_alugados, classificacao_get_categoria);
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
        return;
    }

    Cliente *c = avl_buscar(avl, cpf);
    if (c)
    {
        visualizar_cliente(c);
        return;
    }

    printf("Erro: Cliente nao existe no banco de dados.");
    stop_pressione_continuar();
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
    }
    else if (op == 2)
    {
        buscar_cliente();
    }

    menu();
}

int main(void)
{
    avl = avl_criar(func_compara, func_get_identidade, func_libera);
    classificacao_inicializar();

    menu();

    classificacao_liberar();
    return 0;
}
