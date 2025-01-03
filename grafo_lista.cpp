#include "grafo_lista.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

GrafoLista::GrafoLista() : listaAdj(nullptr), pesosVertices(nullptr), grauVertices(nullptr) {}

GrafoLista::~GrafoLista() {
    if (listaAdj) {
        for (int i = 0; i < ordem; i++) {
            listaAdj[i].~ListaEncadeada();
        }
        free(listaAdj);
    }
    if (pesosVertices) {
        free(pesosVertices);
    }
    if (grauVertices) {
        free(grauVertices);
    }
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

    grauVertices = (int*)calloc(ordem, sizeof(int));
}

void GrafoLista::adicionaAresta(int origem, int destino, int peso) {
    listaAdj[origem - 1].insereNo(destino, peso);
    grauVertices[origem - 1]++; // Incrementa o grau do vértice de origem

    if (!direcionado) {
        listaAdj[destino - 1].insereNo(origem, peso);
        grauVertices[destino - 1]++; // Incrementa o grau do vértice de destino para grafos não direcionados
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

    cout << "Graus dos Vértices:" << endl;
    for (int i = 0; i < ordem; i++) {
        cout << "Vértice " << i + 1 << ": " << grauVertices[i] << endl;
    }
}

bool GrafoLista::eh_completo(){
    for (int i = 0; i < this->ordem; i++) {
        if(this->ordem -1 != this->grauVertices[i])
            return false;
    }

    return true;
}

bool GrafoLista::eh_bipartido() {
    int cor[this->ordem]; // Array para armazenar as cores dos vértices
    int fila[this->ordem]; // Fila circular para BFS
    int inicio, fim;

    // Inicializa as cores como -1 (não visitado)
    for (int i = 0; i < this->ordem; i++) {
        cor[i] = -1;
    }

    // Verifica cada componente do grafo
    for (int v = 0; v < this->ordem; ++v) {
        if (cor[v] != -1) continue; // Já visitado

        // Inicializa a BFS
        inicio = fim = 0;
        fila[fim++] = v;
        cor[v] = 0;

        while (inicio < fim) {
            int atual = fila[inicio++];
            No* no = listaAdj[atual].getCabeca();

            // Processa todos os adjacentes
            while (no != nullptr) {
                int destino = no->destino - 1; // Ajusta índice para base 0
                if (cor[destino] == -1) {
                    cor[destino] = 1 - cor[atual]; // Atribui cor oposta
                    fila[fim++] = destino;        // Adiciona à fila
                } else if (cor[destino] == cor[atual]) {
                    return false; // Encontrou vértices adjacentes com a mesma cor
                }
                no = no->prox;
            }
        }
    }

    return true;
}