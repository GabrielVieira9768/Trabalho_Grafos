# Trabalho de Grafos - Representações em C++

Este é um projeto em C++ que permite a manipulação de grafos utilizando duas representações: lista de adjacência e matriz de adjacência. O código permite tanto a leitura de grafos a partir de arquivos de entrada, além de possibilitar a impressão das informações dos grafos na tela.

## Funcionalidades

O programa possui as seguintes funcionalidades principais:

1. **Exibir o Grafo:** Carrega um grafo a partir de um arquivo de entrada e o exibe na tela, utilizando uma das representações:
   - Matriz de Adjacência
   - Lista de Adjacência

2. **Remoção de Nós:** Permite remover um nó do grafo. Na representação por matriz de adjacência, os IDs dos nós são recalculados automaticamente, gerando um grafo isomorfo ao original.

3. **Remoção de Arestas:** Permite remover a primeira aresta de um nó especificado.

4. **Cálculo da Menor Distância:** Calcula a maior menor distância entre dois nós, permitindo a determinação do caminho mais curto entre eles.

## Como Usar

O programa pode ser executado com diferentes argumentos na linha de comando. Abaixo estão as opções de uso:

### Sintaxe
```bash
./main -d -m|-l <./entradas/arquivo_entrada>
```

### Argumentos
- **-d:** Define a operação desejada.
- **-m:** Utiliza a representação por matriz de adjacência.
- **-l:** Utiliza a representação por lista de adjacência.
- **<arquivo_entrada>:** Caminho para o arquivo de entrada contendo a descrição do grafo.

## Exemplo de Uso
Para carregar um grafo na representação por matriz e exibi-lo:
```bash
./main -d -m ./entradas/grafo.txt
```

Para carregar um grafo na representação por lista e exibi-lo:
```bash
./main -d -l ./entradas/grafo.txt
```

## Observações
- A funcionalidade de recalcular IDs dos nós na representação por matriz garante que a remoção de nós mantenha o grafo isomorfo ao original.
- O cálculo da menor distância é feito utilizando algoritmos eficientes para grafos ponderados.

