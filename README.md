# Trabalho de Grafos - Representações em C++

Este é um projeto em C++ que permite a manipulação de grafos utilizando duas representações: lista de adjacência e matriz de adjacência. O código permite tanto a criação quanto a leitura de grafos a partir de arquivos de entrada, além de possibilitar a impressão dos grafos na tela ou a exportação para um arquivo de saída.

## Funcionalidade

O programa possui as seguintes funcionalidades principais:

1. **Exibir o Grafo**: Carrega um grafo a partir de um arquivo de entrada e o exibe na tela, utilizando uma das representações:
    - Matriz de Adjacência
    - Lista de Adjacência

2. **Criar um Novo Grafo**: Cria um novo grafo a partir de um arquivo de entrada e salva em um arquivo de saída.

## Como Usar

O programa pode ser executado com diferentes argumentos na linha de comando. Abaixo estão as opções de uso:

### Sintaxe
```bash
./main -d|-c -m|-l <./entradas/arquivo_entrada> [arquivo_saida]
