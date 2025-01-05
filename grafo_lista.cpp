#include "grafo_lista.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

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

    cout << "Completo:" << eh_completo() << endl;

    cout << "Bipartido: "<< eh_bipartido() << endl;

    cout << "Conexo:" << n_conexo() << endl;


}

bool GrafoLista::eh_completo(){
    for (int i = 0; i < this->ordem; i++) {
        if(this->ordem -1 != this->grauVertices[i])
            return false;
    }

    return true;
}

bool GrafoLista::eh_bipartido() {
    int n = this->ordem;
    int total = 1 << n; // Número total de subconjuntos (2^n)

    // Percorre todas as divisões possíveis dos vértices em dois conjuntos
    for (int mask = 0; mask < total; ++mask) {
        bool valido = true;

        // Verifica todas as arestas
        for (int v = 0; v < n && valido; ++v) {
            No* no = listaAdj[v].getCabeca();
            while (no != nullptr) {
                int destino = no->destino - 1; // Ajusta índice para base 0

                // Checa se ambos os vértices da aresta estão no mesmo conjunto
                if (((mask >> v) & 1) == ((mask >> destino) & 1)) {
                    valido = false;
                    break;
                }
                no = no->prox;
            }
        }

        // Se encontramos uma divisão válida, o grafo é bipartido
        if (valido) return true;
    }

    // Se nenhuma divisão válida foi encontrada, o grafo não é bipartido
    return false;
}


int GrafoLista::n_conexo() {
    bool visitado[ordem];
    std::fill(visitado, visitado + ordem, false);
    int n_componentes = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            n_componentes++;
            dfs(i, visitado);
        }
    }

    return n_componentes;
}

// Método para auxiliar na busca pelas componentes conexas
void GrafoLista::dfs(int vertice, bool visitado[]) {
    visitado[vertice] = true;
    No* no = listaAdj[vertice].getCabeca();
    while (no) {
        int adj = no->destino - 1;
        if (!visitado[adj]) {
            dfs(adj, visitado);
        }
        no = no->prox;
    }
}