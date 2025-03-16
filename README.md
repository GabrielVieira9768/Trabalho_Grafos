# Trabalho de Grafos - Representações em C++

Este é um projeto em C++ que permite a manipulação de grafos utilizando duas representações: lista de adjacência e matriz de adjacência. O código permite tanto a leitura de grafos a partir de arquivos de entrada, além de possibilitar a impressão das informações dos grafos na tela e a geração de uma Árvore de Steiner.

## Funcionalidades

O programa possui as seguintes funcionalidades principais:

1) **Algoritmo Guloso para Árvore de Steiner:** Implementação do algoritmo guloso para encontrar uma árvore de Steiner em um grafo, considerando um conjunto de nós terminais e a minimização do custo total das arestas.

2) **Algoritmo Randomizado:** Algoritmo de abordagem randomizada para resolver problemas de otimização no grafo, oferecendo soluções alternativas para o problema da árvore de Steiner.

3) **Algoritmo Reativo:** Implementação de um algoritmo reativo para melhorar a eficiência e qualidade das soluções, ajustando dinamicamente os parâmetros de busca durante a execução, de acordo com as condições do grafo.

## Compilação
```bash
g++ -o main.out main.cpp src/*.cpp -I./include/ -g -Wall -Werror
```

### Execução
```bash
time|valgrind main.out -p -m|-l ./entradas/<arquivo_entrada>.txt
```

### Argumentos
- **-p:** Define a operação desejada.
- **-m:** Utiliza a representação por matriz de adjacência.
- **-l:** Utiliza a representação por lista de adjacência.
- **<arquivo_entrada>:** Caminho para o arquivo de entrada contendo a descrição do grafo.

## Exemplo de Uso
Para carregar um grafo na representação por matriz e gerar a árvore de Steiner:
```bash
main.out -p -m ./entradas/grafo.txt
```

Para carregar um grafo na representação por lista e gerar a árvore de Steiner:
```bash
main.out -p -l ./entradas/grafo.txt
```