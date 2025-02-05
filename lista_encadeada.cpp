#include "lista_encadeada.h"

using namespace std;

// Construtor da Aresta
Aresta::Aresta(int destino, int peso) : destino(destino), peso(peso), proxima(nullptr) {}

// Construtor do Nó
No::No(int id, int peso) : id(id), peso(peso), grau(0), listaArestas(nullptr), proximo(nullptr) {}

// Construtor da Lista Encadeada
ListaEncadeada::ListaEncadeada() : cabeca(nullptr) {}

// Destrutor da Lista Encadeada
ListaEncadeada::~ListaEncadeada() {
    while (cabeca) {
        No* temp = cabeca;
        cabeca = cabeca->proximo;
        
        Aresta* arestaAtual = temp->listaArestas;
        while (arestaAtual) {
            Aresta* tempAresta = arestaAtual;
            arestaAtual = arestaAtual->proxima;
            delete tempAresta;
        }
        
        delete temp;
    }
}

// Retorna um nó da lista
No* ListaEncadeada::getNo(int id) {
    No* atual = cabeca;
    
    while (atual) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return nullptr;
}

// Retorna uma aresta da lista
Aresta* ListaEncadeada::getAresta(int origem, int destino) {
    No* noOrigem = getNo(origem);
    if (!noOrigem) return nullptr;

    Aresta* atual = noOrigem->listaArestas;
    while (atual) {
        if (atual->destino == destino) {
            return atual;
        }
        atual = atual->proxima;
    }
    return nullptr;
}

void ListaEncadeada::setCabeca(No* novoCabeca) {
    cabeca = novoCabeca;
}

// Imprime a lista encadeada
void ListaEncadeada::imprimeLista() {
    No* atual = cabeca;
    while (atual) {
        cout << "No " << atual->id << " [" << atual->peso << "] -> ";
        Aresta* arestaAtual = atual->listaArestas;
        while (arestaAtual) {
            cout << "(" << arestaAtual->destino << ", " << arestaAtual->peso << ") -> ";
            arestaAtual = arestaAtual->proxima;
        }
        cout << "NULL\n";
        atual = atual->proximo;
    }
}