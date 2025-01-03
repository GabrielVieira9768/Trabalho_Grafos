#include "Grafo.h"
#include "grafo_lista.h"

using namespace std;

// Construtor
GrafoLista::GrafoLista(int n) : numero_vertices(n) {
    lista_adj = new No*[n];
    for (int i = 0; i < n; i++) {
        lista_adj[i] = nullptr;
    }
}

// Destrutor
GrafoLista::~GrafoLista() {
    for (int i = 0; i < numero_vertices; i++) {
        No* atual = lista_adj[i];
        while (atual != nullptr) {
            No* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }
    delete[] lista_adj;
}

// Adiciona uma aresta entre dois vértices
void GrafoLista::adicionarAresta(int u, int v) {
    // Adiciona v na lista de u
    No* novo1 = new No{v, lista_adj[u]};
    lista_adj[u] = novo1;

    // Adiciona u na lista de v (grafo não direcionado)
    No* novo2 = new No{u, lista_adj[v]};
    lista_adj[v] = novo2;
}

// Verifica se o grafo é bipartido
bool GrafoLista::eh_bipartido() {
    int* cor = new int[numero_vertices];
    for (int i = 0; i < numero_vertices; i++) {
        cor[i] = -1;
    }

    // Realiza uma busca em profundidade para verificar a bipartição
    for (int i = 0; i < numero_vertices; i++) {
        if (cor[i] == -1) { // Se o vértice não foi visitado
            cor[i] = 0; // Começa com a cor 0
            bool bipartido = true;
            No* atual = lista_adj[i];
            while (atual != nullptr) {
                if (cor[atual->vertice] == -1) {
                    cor[atual->vertice] = 1 - cor[i];
                } else if (cor[atual->vertice] == cor[i]) {
                    bipartido = false;
                    break;
                }
                atual = atual->prox;
            }
            if (!bipartido) {
                delete[] cor;
                return false;
            }
        }
    }

    delete[] cor;
    return true;
}

// Retorna o número de componentes conexas
int GrafoLista::n_conexo() {
    bool* visitado = new bool[numero_vertices];
    for (int i = 0; i < numero_vertices; i++) {
        visitado[i] = false;
    }

    int componentes = 0;

    // Realiza uma busca em profundidade para contar componentes conexas
    for (int i = 0; i < numero_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            No* atual = lista_adj[i];
            visitado[i] = true;
            while (atual != nullptr) {
                if (!visitado[atual->vertice]) {
                    visitado[atual->vertice] = true;
                }
                atual = atual->prox;
            }
        }
    }

    delete[] visitado;
    return componentes;
}