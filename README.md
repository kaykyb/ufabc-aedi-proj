# UFABCars - Sistema de Gerenciamento de Clientes

> Este documento foi parcialmente criado com apoio de Inteligência Artificial

Sistema de classificação e gerenciamento de clientes para locadora de veículos, desenvolvido como projeto da disciplina de Algoritmos e Estruturas de Dados I da UFABC.

## Descrição

O UFABCars é um sistema que permite cadastrar, buscar e gerenciar clientes de uma locadora de veículos. O sistema classifica automaticamente os clientes em categorias com base em diversos critérios, utilizando estruturas de dados eficientes como árvores AVL e árvores de decisão.

## Estruturas de Dados Implementadas

- **Árvore AVL**: Armazena e organiza os clientes de forma balanceada, permitindo busca, inserção e remoção eficientes em O(log n)
- **Árvore de Decisão**: Classifica clientes em categorias baseadas em múltiplos atributos
- **TAD Cliente**: Encapsula as informações e operações relacionadas aos clientes

## Funcionalidades

- Cadastro de novos clientes com validação de dados
- Busca de clientes por CPF
- Edição de informações dos clientes:
  - Idade
  - Anos de CNH permanente
  - Status de inadimplência
  - Número de acidentes causados
  - Gastos anuais na locadora
  - Dias de aluguel no ano
- Classificação automática em categorias

## Estrutura do Projeto

```
.
├── src/
│   ├── lib/              # Bibliotecas principais
│   │   ├── avl.c/h       # Implementação da árvore AVL
│   │   ├── cliente.c/h   # TAD Cliente
│   │   └── decisao.c/h   # Árvore de decisão
│   ├── armazenamento.c/h # Gerenciamento de dados
│   ├── classificacao.c/h # Lógica de classificação
│   ├── validacao.c/h     # Validação de entradas
│   └── main.c            # Interface do usuário
├── test/                 # Testes unitários
├── bin/                  # Executáveis compilados
├── obj/                  # Arquivos objeto
└── lib/                  # Bibliotecas estáticas
```

## Compilação

O projeto oferece duas opções de compilação:

### Opção 1: Usando Make (Recomendado)

```bash
# Compilar o projeto
make

# Compilar e executar testes
make test

# Limpar arquivos compilados
make clean
```

### Opção 2: Usando CMake

```bash
# Criar diretório de build
mkdir build && cd build

# Configurar o projeto
cmake ..

# Compilar
cmake --build .

# Executar testes
ctest
```

## Execução

Após compilar com Make:

```bash
./bin/ufabc_aedi_proj
```

Após compilar com CMake:

```bash
./ufabc_aedi_proj
```

## Testes

O projeto inclui testes unitários para todas as estruturas de dados:

### Testes de Cliente

- Criação de cliente
- Atualização de idade, CNH, inadimplência, acidentes, gastos e dias alugados

### Testes de AVL

- Criação de árvore vazia
- Inserção simples e múltipla
- Rotações (direita, esquerda, esquerda-direita, direita-esquerda)
- Busca de elementos

### Testes de Árvore de Decisão

- Nós folha (resultados)
- Árvores simples
- Árvores complexas

Para executar os testes:

```bash
make test
```

## Requisitos

- Compilador C compatível com C11 (gcc, clang, etc.)
- Make (para compilação via Makefile)
- CMake 3.5+ (para compilação via CMake)

## Validações Implementadas

O sistema valida:

- CPF com 11 dígitos numéricos
- Idade entre 18 e 120 anos
- Anos de CNH compatíveis com a idade (máximo: idade - 18)
- Status de inadimplência (0 ou 1)
- Número de acidentes não-negativo
- Gastos não-negativos
- Dias alugados entre 0 e 366

## Autores

- Igor Domingos da Silva Mozetic
- Joao Pedro Pina Neves
- Kayky de Brito Dos Santos
- Marco Antonio Lopes Rodrigues
- Pedro Henrique Cardoso Silva
