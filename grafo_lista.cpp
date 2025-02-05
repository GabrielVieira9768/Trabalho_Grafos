#include "grafo_lista.h"

using namespace std;

GrafoLista::GrafoLista() {
    listaNos = new ListaEncadeada();
}

GrafoLista::~GrafoLista() {
    delete listaNos;
}

void GrafoLista::novo_no(int id, int peso) {
    listaNos->insereNo(id, peso);
}

void GrafoLista::deleta_no(int id) {
    listaNos->removeNo(id);
}

void GrafoLista::nova_aresta(int origem, int destino, int peso) {
    No* noOrigem = listaNos->getNo(origem);
    if (noOrigem) {
        noOrigem->listaArestas.insereAresta(destino, peso);
    }
}

void GrafoLista::deleta_aresta(int origem, int destino) {
    listaNos->removeAresta(origem, destino);
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