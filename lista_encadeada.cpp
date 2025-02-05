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
    
    Aresta* arestaAtual = atual->listaArestas;
    while (arestaAtual) {
        Aresta* tempAresta = arestaAtual;
        arestaAtual = arestaAtual->proxima;
        delete tempAresta;
    }

    delete atual;
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

// Insere uma aresta no primeiro nó da lista
void ListaEncadeada::insereAresta(int destino, int peso) {
    if (!cabeca) return;

    Aresta* novaAresta = new Aresta(destino, peso);
    novaAresta->proxima = cabeca->listaArestas;
    cabeca->listaArestas = novaAresta;

    cabeca->grau++;
}

// Remove uma aresta de um nó
void ListaEncadeada::removeAresta(int origem, int destino) {
    No* atual = cabeca;

    while (atual && atual->id != origem) {
        atual = atual->proximo;
    }

    if (!atual) return;

    Aresta* arestaAtual = atual->listaArestas;
    Aresta* anterior = nullptr;

    while (arestaAtual && arestaAtual->destino != destino) {
        anterior = arestaAtual;
        arestaAtual = arestaAtual->proxima;
    }

    if (!arestaAtual) return;

    if (anterior) {
        anterior->proxima = arestaAtual->proxima;
    } else {
        atual->listaArestas = arestaAtual->proxima;
    }

    delete arestaAtual;
    atual->grau--;
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