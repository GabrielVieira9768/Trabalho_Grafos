#include "./grafo_matriz.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

using namespace std;

GrafoMatriz::GrafoMatriz() : capacidade(10), matrizAdj(nullptr), pesosVertices(nullptr) {
    matrizAdj = new float*[capacidade];
    for (int i = 0; i < capacidade; i++) {
        matrizAdj[i] = new float[capacidade](); // Inicializa com 0
    }

    if (verticePonderado) {
        pesosVertices = new float[capacidade](); // Inicializa com 0
    }
}

GrafoMatriz::~GrafoMatriz() {
    if (matrizAdj) {
        for (int i = 0; i < ordem; i++) {
            delete[] matrizAdj[i];
        }
        delete[] matrizAdj;
    }
    delete[] pesosVertices;
}

void GrafoMatriz::redimensionarMatriz() {
    int novaCapacidade = capacidade * 2;

    // Aloca uma nova matriz com o dobro do tamanho
    float** novaMatriz = new float*[novaCapacidade];
    for (int i = 0; i < novaCapacidade; i++) {
        novaMatriz[i] = new float[novaCapacidade]();
    }

    // Copia os valores da matriz antiga para a nova
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            novaMatriz[i][j] = matrizAdj[i][j];
        }
    }

    // Libera a memória da matriz antiga
    for (int i = 0; i < capacidade; i++) {
        delete[] matrizAdj[i];
    }
    delete[] matrizAdj;

    // Atualiza a matriz e a capacidade
    matrizAdj = novaMatriz;
    capacidade = novaCapacidade;
}

int* GrafoMatriz::getVizinhos(int id) {
    id--; // Ajusta o índice para começar de 0
    int* vizinhos = new int[ordem]; // Aloca um array para os vizinhos
    int count = 0;

    for (int i = 0; i < ordem; i++) {
        if (matrizAdj[id][i] != 0) { // Se há uma aresta entre id e i
            vizinhos[count++] = i + 1; // Adiciona o vizinho (ajusta o índice para começar de 1)
        }
    }

    // Redimensiona o array para o tamanho correto
    int* resultado = new int[count];
    for (int i = 0; i < count; i++) {
        resultado[i] = vizinhos[i];
    }

    delete[] vizinhos; // Libera o array temporário
    return resultado;
}

int GrafoMatriz::getGrau(int id) {
    id--; // Ajusta o índice para começar de 0
    int grau = 0;

    for (int i = 0; i < ordem; i++) {
        if (matrizAdj[id][i] != 0) { // Conta as arestas de saída
            grau++;
        }
        if (!direcionado && matrizAdj[i][id] != 0) { // Se não for direcionado, conta as arestas de entrada
            grau++;
        }
    }

    return grau;
}

void GrafoMatriz::novo_no(int id, float peso) {
    // Verifica se a capacidade é suficiente
    if (ordem >= capacidade) {
        redimensionarMatriz();
    }

    // Adiciona o nó
    if (verticePonderado) {
        pesosVertices[id - 1] = peso;
    }

    ordem++;
}

void GrafoMatriz::deleta_no(int id) {
    if (id < 1 || id > ordem) {
        cerr << "Erro: ID do nó inválido." << endl;
        return;
    }

    // Remove o nó e recalcula os IDs
    for (int i = id - 1; i < ordem - 1; i++) {
        pesosVertices[i] = pesosVertices[i + 1]; // Atualiza os pesos dos vértices
        for (int j = 0; j < ordem; j++) {
            matrizAdj[i][j] = matrizAdj[i + 1][j]; // Atualiza as arestas
            matrizAdj[j][i] = matrizAdj[j][i + 1];
        }
    }

    cout << "Excluindo nó " << id << "..." << endl;
    
    ordem--;
}

void GrafoMatriz::nova_aresta(int origem, int destino, float peso) {
    origem--;
    destino--;

    matrizAdj[origem][destino] = peso;

    if (!direcionado) {
        matrizAdj[destino][origem] = peso;
    }
}

void GrafoMatriz::deleta_aresta(int origem, int destino) {
    origem--;
    destino--;

    if (origem < 0 || origem >= ordem || destino < 0 || destino >= ordem) {
        cerr << "Erro: Índices fora dos limites." << endl;
        return;
    }

    matrizAdj[origem][destino] = 0; // Remove a aresta

    if (!direcionado) {
        matrizAdj[destino][origem] = 0; // Remove também no caso de grafo não direcionado
    }
}

bool GrafoMatriz::existeAresta(int origem, int destino) {
    origem--;
    destino--;

    if (origem < 0 || origem >= ordem || destino < 0 || destino >= ordem) {
        return false; // Índices fora dos limites
    }

    return matrizAdj[origem][destino] != 0; // Aresta existe se o peso for diferente de 0
}

float GrafoMatriz::getPesoAresta(int origem, int destino) {
    origem--;
    destino--;

    if (origem < 0 || origem >= ordem || destino < 0 || destino >= ordem) {
        return 0; // Índices fora dos limites
    }

    return matrizAdj[origem][destino]; // Retorna o peso da aresta
}

void GrafoMatriz::imprimeMatriz() {
    cout << "Matriz de Adjacência:" << endl;

    // Cabeçalho com os índices dos vértices
    cout << setw(4) << " ";
    for (int i = 0; i < ordem; i++) {
        cout << setw(4) << (i + 1);
    }
    cout << endl;

    // Impressão da matriz
    for (int i = 0; i < ordem; i++) {
        cout << setw(4) << (i + 1);  // Índice da linha
        for (int j = 0; j < ordem; j++) {
            cout << setw(4) << matrizAdj[i][j];
        }
        cout << endl;
    }
}