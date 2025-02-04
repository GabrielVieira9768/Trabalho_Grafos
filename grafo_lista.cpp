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
        // Criar nova aresta e adicioná-la à lista de arestas do nó de origem
        Aresta* novaAresta = new Aresta(destino, peso);
        novaAresta->proxima = noOrigem->listaArestas;
        noOrigem->listaArestas = novaAresta;
    }
}

void GrafoLista::deleta_aresta(int origem, int destino) {
    listaNos->removeAresta(origem, destino);
}

// void GrafoLista::imprimeGrafo() {
//     listaNos->imprimeLista();
// }