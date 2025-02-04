#include "ListaEncadeada.h"

using namespace std;

// Construtor da Aresta
Aresta::Aresta(int destino, int peso) : destino(destino), peso(peso), proxima(nullptr) {}

// Construtor do Nó
No::No(int id, int peso) : id(id), peso(peso), listaArestas(nullptr), proximo(nullptr) {}

// Construtor da Lista Encadeada
ListaEncadeada::ListaEncadeada() : cabeca(nullptr) {}

// Destrutor da Lista Encadeada
ListaEncadeada::~ListaEncadeada() {
    while (cabeca) {
        No* temp = cabeca;
        cabeca = cabeca->proximo;
        
        // Remove todas as arestas do nó
        Aresta* arestaAtual = temp->listaArestas;
        while (arestaAtual) {
            Aresta* tempAresta = arestaAtual;
            arestaAtual = arestaAtual->proxima;
            delete tempAresta;
        }
        
        delete temp;
    }
}

// Insere um novo nó na lista
void ListaEncadeada::insereNo(int id, int peso) {
    No* novoNo = new No(id, peso);
    novoNo->proximo = cabeca;
    cabeca = novoNo;
}

// Remove um nó e todas as suas arestas
void ListaEncadeada::removeNo(int id) {
    No* atual = cabeca;
    No* anterior = nullptr;

    while (atual && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) return; // Nó não encontrado

    if (anterior) {
        anterior->proximo = atual->proximo;
    } else {
        cabeca = atual->proximo;
    }

    // Remove todas as arestas associadas ao nó
    Aresta* arestaAtual = atual->listaArestas;
    while (arestaAtual) {
        Aresta* tempAresta = arestaAtual;
        arestaAtual = arestaAtual->proxima;
        delete tempAresta;
    }

    delete atual;
}

// Insere uma aresta no primeiro nó da lista
void ListaEncadeada::insereAresta(int destino, int peso) {
    if (!cabeca) return; // Lista vazia

    Aresta* novaAresta = new Aresta(destino, peso);
    novaAresta->proxima = cabeca->listaArestas;
    cabeca->listaArestas = novaAresta;
}

// Remove uma aresta de um nó específico
void ListaEncadeada::removeAresta(int origem, int destino) {
    No* atual = cabeca;

    while (atual && atual->id != origem) {
        atual = atual->proximo;
    }

    if (!atual) return; // Nó de origem não encontrado

    Aresta* arestaAtual = atual->listaArestas;
    Aresta* anterior = nullptr;

    while (arestaAtual && arestaAtual->destino != destino) {
        anterior = arestaAtual;
        arestaAtual = arestaAtual->proxima;
    }

    if (!arestaAtual) return; // Aresta não encontrada

    if (anterior) {
        anterior->proxima = arestaAtual->proxima;
    } else {
        atual->listaArestas = arestaAtual->proxima;
    }

    delete arestaAtual;
}

// Imprime a lista encadeada
void ListaEncadeada::imprimeLista() {
    No* atual = cabeca;
    while (atual) {
        cout << "No " << atual->id << " [" << atual->peso << "] -> ";
        Aresta* arestaAtual = atual->listaArestas;
        while (arestaAtual) {
            cout << "(Destino: " << arestaAtual->destino << ", Peso: " << arestaAtual->peso << ") -> ";
            arestaAtual = arestaAtual->proxima;
        }
        cout << "NULL\n";
        atual = atual->proximo;
    }
}