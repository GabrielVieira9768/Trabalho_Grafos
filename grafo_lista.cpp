#include "grafo_lista.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

GrafoLista::GrafoLista() : listaAdj(nullptr), pesosVertices(nullptr) {}

GrafoLista::~GrafoLista() {
    if (listaAdj) {
        for (int i = 0; i < ordem; i++) {
            listaAdj[i].~ListaEncadeada();
        }
        free(listaAdj);
    }
    // free(pesosVertices);
}

void GrafoLista::inicializaLista(int ordem) {
    this->ordem = ordem;
    listaAdj = (ListaEncadeada*)malloc(ordem * sizeof(ListaEncadeada));
    for (int i = 0; i < ordem; i++) {
        new(&listaAdj[i]) ListaEncadeada();
    }

    if (verticePonderado) {
        pesosVertices = (int*)calloc(ordem, sizeof(int));
    }
}

void GrafoLista::adicionaAresta(int origem, int destino, int peso) {
    listaAdj[origem - 1].insereNo(destino, peso);
    if (!direcionado) {
        listaAdj[destino - 1].insereNo(origem, peso);
    }
}

void GrafoLista::carregaGrafo(const string& arquivo) {
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

    inicializaLista(ordem);

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

void GrafoLista::imprimeGrafo() {
    cout << "Lista de Adjacência:" << endl;
    for (int i = 0; i < ordem; i++) {
        cout << i + 1 << ": ";
        listaAdj[i].imprimeLista();
        cout << endl;
    }

    if (verticePonderado) {
        cout << "Pesos dos Vértices:" << endl;
        for (int i = 0; i < ordem; i++) {
            cout << pesosVertices[i] << " ";
        }
        cout << endl;
    }
}
