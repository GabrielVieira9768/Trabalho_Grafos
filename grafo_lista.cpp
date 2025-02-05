#include "grafo_lista.h"

using namespace std;

GrafoLista::GrafoLista() {
    listaNos = new ListaEncadeada();
}

GrafoLista::~GrafoLista() {
    delete listaNos;
}

void GrafoLista::novo_no(int id, int peso) {
    No* novoNo = new No(id, peso);
    novoNo->proximo = listaNos->cabeca;
    listaNos->cabeca = novoNo;
}

void GrafoLista::deleta_no(int id) {
    No* atual = listaNos->cabeca;
    No* anterior = nullptr;
    
    while (atual && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!atual) return;
    
    Aresta* arestaAtual = atual->listaArestas;
    while (arestaAtual) {
        Aresta* tempAresta = arestaAtual;
        arestaAtual = arestaAtual->proxima;
        delete tempAresta;
    }
    
    if (anterior) {
        anterior->proximo = atual->proximo;
    } else {
        listaNos->cabeca = atual->proximo;
    }
    
    delete atual;
}

void GrafoLista::nova_aresta(int origem, int destino, int peso) {
    No* noOrigem = listaNos->cabeca;
    
    while (noOrigem && noOrigem->id != origem) {
        noOrigem = noOrigem->proximo;
    }
    
    if (!noOrigem) return;
    
    Aresta* novaAresta = new Aresta(destino, peso);
    novaAresta->proxima = noOrigem->listaArestas;
    noOrigem->listaArestas = novaAresta;
    noOrigem->grau++;
}

void GrafoLista::deleta_aresta(int origem, int destino) {
    No* atual = listaNos->cabeca;
    
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

// Verifica se existe um nó específico
bool GrafoLista::existeNo(int id) {
    if(!listaNos->getNo(id))
        return false;
    return true;
}

// Verifica se existe uma aresta específica
bool GrafoLista::existeAresta(int origem, int destino) {
    if(!listaNos->getAresta(int origem, int destino);)
        return false;
    return true;
}

// Retorna o Grau de um vértice
int GrafoLista::getGrau(int id) {
    No* no = listaNos->getNo(id);
    return (no != nullptr) ? no->grau : -1;
}

// Retorna um array com todos os vizinho de um nó
int* GrafoLista::getVizinhos(int id) {
    No* no = listaNos->getNo(id);
    if (!no) {
        return nullptr;
    }
    
    int* vizinhos = new int[no->grau];
    
    aresta = no->listaArestas;
    for (int i = 0; i < no->grau; i++) {
        vizinhos[i] = aresta->destino;
        aresta = aresta->proxima;
    }

    return vizinhos;
}

// Retorna o número de arestas do grafo
int GrafoLista::getNumArestas() {
    int numArestas = 0;
    No* atual = listaNos->getCabeca();

    while (atual) {
        numArestas += atual->grau;
        atual = atual->proximo;
    }
    
    if(!direcionado)
        numArestas = numArestas / 2;

    return numArestas;
}

void GrafoLista::imprimeLista() {
    listaNos->imprimeLista();
}