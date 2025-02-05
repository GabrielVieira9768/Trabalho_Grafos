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

// Retorna um array com todos os vizinho de um nó
int* GrafoLista::getVizinhos(int id) {
    No* no = listaNos->getNo(id);
    if (!no) {
        return nullptr; // Retorna nullptr se o nó não existir
    }
    
    // Alocar array dinâmico para armazenar os ids dos vizinhos
    int* vizinhos = new int[no->grau];
    
    // Preencher o array com os ids dos vizinhos
    aresta = no->listaArestas;
    for (int i = 0; i < no->grau; i++) {
        vizinhos[i] = aresta->destino;
        aresta = aresta->proxima;
    }

    return vizinhos;
}

// void GrafoLista::imprimeGrafo() {
//     listaNos->imprimeLista();
// }