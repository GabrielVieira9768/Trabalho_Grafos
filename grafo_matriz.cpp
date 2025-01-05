#include "grafo_matriz.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

using namespace std;

GrafoMatriz::GrafoMatriz() : matrizAdj(nullptr), pesosVertices(nullptr) {}

GrafoMatriz::~GrafoMatriz() {
    if (matrizAdj) {
        for (int i = 0; i < ordem; i++) {
            free(matrizAdj[i]);
        }
        free(matrizAdj);
    }
    free(pesosVertices);
}

void GrafoMatriz::inicializaMatriz(int ordem) {
    this->ordem = ordem;
    matrizAdj = (int**)malloc(ordem * sizeof(int*));
    for (int i = 0; i < ordem; i++) {
        matrizAdj[i] = (int*)calloc(ordem, sizeof(int));
    }

    if (verticePonderado) {
        pesosVertices = (int*)calloc(ordem, sizeof(int));
    }
}

void GrafoMatriz::adicionaAresta(int origem, int destino, int peso) {
    matrizAdj[origem - 1][destino - 1] = peso;
    if (!direcionado) {
        matrizAdj[destino - 1][origem - 1] = peso;
    }
}

void GrafoMatriz::carregaGrafo(const string& arquivo) {
    ifstream entrada(arquivo.c_str());
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string linha;

    // Lê a primeira linha com as configurações do grafo
    if (getline(entrada, linha)) {
        char* end;
        ordem = strtol(linha.c_str(), &end, 10);
        direcionado = (strtol(end, &end, 10) == 1);
        verticePonderado = (strtol(end, &end, 10) == 1);
        arestaPonderada = (strtol(end, &end, 10) == 1);
    }

    inicializaMatriz(ordem);

    // Lê os pesos dos vértices, se houver
    if (verticePonderado && getline(entrada, linha)) {
        char* token = strtok(const_cast<char*>(linha.c_str()), " ");
        for (int i = 0; i < ordem && token; i++) {
            pesosVertices[i] = atoi(token);
            token = strtok(nullptr, " ");
        }
    }

    // Lê as arestas do grafo
    while (getline(entrada, linha)) {
        char* end;
        int origem = strtol(linha.c_str(), &end, 10);
        int destino = strtol(end, &end, 10);
        int peso = arestaPonderada ? strtol(end, &end, 10) : 1;

        adicionaAresta(origem, destino, peso);
    }

    entrada.close();
}

void GrafoMatriz::imprimeGrafo() {
    cout << "Matriz de Adjacência:" << endl;
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            cout << setw(3) << matrizAdj[i][j];
        }
        cout << endl;
    }

    if (verticePonderado) {
        cout << "Pesos dos Vértices:" << endl;
        for (int i = 0; i < ordem; i++) {
            cout << pesosVertices[i] << " ";
        }
        cout << endl;
    }
    cout << "Completo: " << eh_completo();
}

bool GrafoMatriz::eh_completo() {
    for (int i = 0; i < ordem; ++i) {
        for (int j = 0; j < ordem; ++j) {
            if (i != j && matrizAdj[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}