#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lib/avl.h"
#include "lib/cliente.h"
#include "armazenamento.h"
#include "validacao.h"

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

// Interface
int editor(Cliente *c)
{
    printf("\n=================================================\n");
    printf("Opções:\n");
    printf("[I] Alterar Idade         [C] Alterar Anos de CNH\n");
    printf("[P] Alterar Inadimplente  [A] Alterar Acidentes\n");
    printf("[G] Alterar Gastos        [D] Alterar D. Alugados\n");
    printf("[V] Voltar ao menu\n");
    printf("-------------------------------------------------\n");
    printf("Digite a opcao: ");

    char opcao;
    scanf(" %c", &opcao);
    limpar_buffer_entrada();

    if (opcao == 'V' || opcao == 'v')
    {
        return 0;
    }

    if (opcao == 'I' || opcao == 'i')
    {
        int nova_idade;
        printf("Nova idade: ");
        if (scanf("%d", &nova_idade) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_idade(nova_idade))
        {
            printf("Erro: Idade deve estar entre 18 e 120 anos.\n");
            stop_pressione_continuar();
            return 1;
        }

        if (cliente_anos_cnh(c) > (nova_idade - 18))
        {
            printf("Erro: Anos de CNH (%d) incompativel com a nova idade.\n", cliente_anos_cnh(c));
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_idade(c, nova_idade);
        return 1;
    }

    if (opcao == 'C' || opcao == 'c')
    {
        int novos_anos_cnh;
        printf("Novos anos de CNH: ");
        if (scanf("%d", &novos_anos_cnh) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_anos_cnh(novos_anos_cnh, cliente_idade(c)))
        {
            printf("Erro: Anos de CNH invalido.\n");
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_anos_cnh(c, novos_anos_cnh);
        return 1;
    }

    if (opcao == 'P' || opcao == 'p')
    {
        int inadimplente;
        printf("Inadimplente? (1 para sim, 0 para nao): ");
        if (scanf("%d", &inadimplente) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_inadimplente(inadimplente))
        {
            printf("Erro: Valor deve ser 0 ou 1.\n");
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_inadimplente(c, inadimplente);
        return 1;
    }

    if (opcao == 'A' || opcao == 'a')
    {
        int novos_acidentes;
        printf("Novo numero de acidentes: ");
        if (scanf("%d", &novos_acidentes) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_acidentes(novos_acidentes))
        {
            printf("Erro: Numero de acidentes nao pode ser negativo.\n");
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_acidentes(c, novos_acidentes);
        return 1;
    }

    if (opcao == 'G' || opcao == 'g')
    {
        float novos_gastos;
        printf("Novos gastos: ");
        if (scanf("%f", &novos_gastos) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_gastos(novos_gastos))
        {
            printf("Erro: Gastos nao podem ser negativos.\n");
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_gastos(c, novos_gastos);
        return 1;
    }

    if (opcao == 'D' || opcao == 'd')
    {
        int novos_dias;
        printf("Novos dias alugados: ");
        if (scanf("%d", &novos_dias) != 1)
        {
            printf("Erro: Entrada invalida.\n");
            limpar_buffer_entrada();
            stop_pressione_continuar();
            return 1;
        }
        limpar_buffer_entrada();

        if (!valida_dias_alugados(novos_dias))
        {
            printf("Erro: Dias de aluguel deve estar entre 0 e 366.\n");
            stop_pressione_continuar();
            return 1;
        }

        cliente_atualiza_dias_alugados(c, novos_dias);
        return 1;
    }

    printf("Opcao invalida!\n");
    stop_pressione_continuar();
    return 1;
}

void visualizar_cliente(Cliente *c)
{
    do
    {
        clear();
        header("Visualizar Cliente");

        printf("CPF:                  %s\n", cliente_cpf(c));
        printf("Categoria do Cliente: ");
        cliente_print_categoria(c);
        printf("\n");

        printf("-------------------------------------------------\n");

        printf("Idade:                %d anos\n", cliente_idade(c));
        printf("Anos de CNH:          %d anos\n", cliente_anos_cnh(c));

        printf("Inadimplente:         ");
        if (cliente_inadimplente(c))
        {
            printf("Sim\n");
        }
        else
        {
            printf("Nao\n");
        }

        printf("Acidentes:            %d\n", cliente_acidentes(c));
        printf("Gastos:               R$ %.2f\n", cliente_gastos(c));
        printf("Dias Alugados no Ano: %d dias\n", cliente_dias_alugados(c));
    } while (editor(c));
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

    if (!valida_cpf(cpf))
    {
        printf("Erro: CPF invalido.\n");
        stop_pressione_continuar();
        return;
    }

    if (armazenamento_buscar_cliente(cpf))
    {
        printf("Erro: Cliente ja existe no banco de dados...");
        stop_pressione_continuar();
        return;
    };

    int idade;
    printf("Idade: ");
    if (scanf("%d", &idade) != 1)
    {
        printf("Erro: Entrada invalida para idade.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    if (!valida_idade(idade))
    {
        printf("Erro: Idade deve estar entre 18 e 120 anos.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    int anos_cnh;
    printf("Anos de CNH permanente: ");
    if (scanf("%d", &anos_cnh) != 1)
    {
        printf("Erro: Entrada invalida para anos de CNH.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    if (!valida_anos_cnh(anos_cnh, idade))
    {
        printf("Erro: Anos de CNH invalido.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    int inadimplente;
    printf("O cliente esta inadimplente? (1 para sim, 0 para nao): ");
    if (scanf("%d", &inadimplente) != 1)
    {
        printf("Erro: Entrada invalida para inadimplente.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    if (!valida_inadimplente(inadimplente))
    {
        printf("Erro: Inadimplente deve ser '0' ou '1'.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    int acidentes;
    printf("Numero de acidentes causados: ");
    if (scanf("%d", &acidentes) != 1)
    {
        printf("Erro: Entrada invalida para numero de acidentes.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    if (!valida_acidentes(acidentes))
    {
        printf("Erro: Numero de acidentes nao pode ser negativo.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    float gastos;
    printf("Gastos na loja neste ano: ");
    if (scanf("%f", &gastos) != 1)
    {
        printf("Erro: Entrada invalida para gastos.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    if (!valida_gastos(gastos))
    {
        printf("Erro: Gastos nao podem ser negativos.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }

    int dias_alugados;
    printf("Dias de aluguel neste ano: ");
    if (scanf("%d", &dias_alugados) != 1)
    {
        printf("Erro: Entrada invalida para dias de aluguel.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    if (!valida_dias_alugados(dias_alugados))
    {
        printf("Erro: Dias de aluguel deve estar entre 0 e 366.\n");
        limpar_buffer_entrada();
        stop_pressione_continuar();
        return;
    }
    getchar();

    Cliente *c = armazenamento_criar_cliente(cpf, idade, anos_cnh, inadimplente, acidentes, gastos, dias_alugados);
    if (!c)
    {
        printf("Erro: Falha ao criar cliente no banco de dados.\n");
        stop_pressione_continuar();
        return;
    }
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

    if (!valida_cpf(cpf))
    {
        printf("Erro: CPF invalido.\n");
        stop_pressione_continuar();
        return;
    }

    Cliente *c = armazenamento_buscar_cliente(cpf);
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
    printf("[3] Sair do Programa\n");
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
    else if (op == 3)
    {
        return;
    }

    menu();
}

int main(void)
{
    armazenamento_inicializar();

    menu();

    armazenamento_liberar();
    return 0;
}
