#include "./grafo_lista.h"

using namespace std;

GrafoLista::GrafoLista() {
    listaNos = new ListaEncadeada();
}

GrafoLista::~GrafoLista() {
    delete listaNos;
}

void GrafoLista::novo_no(int id, int peso) {
    No* novoNo = new No(id, peso);
    novoNo->proximo = listaNos->getCabeca();
    listaNos->setCabeca(novoNo);
    ordem++;
}

void GrafoLista::deleta_no(int id) {
    No* noParaRemover = listaNos->getNo(id);
    if (!noParaRemover) return;
    
    // Remover todas as arestas que apontam para o nó a ser removido
    No* atual = listaNos->getCabeca();
    while (atual) {
        if (atual->id != id) {
            deleta_aresta(atual->id, id);
        }
        atual = atual->proximo;
    }
    
    // Remover todas as arestas do nó
    Aresta* arestaAtual = noParaRemover->listaArestas;
    while (arestaAtual) {
        Aresta* tempAresta = arestaAtual;
        arestaAtual = arestaAtual->proxima;
        delete tempAresta;
    }
    
    // Remover o nó da lista de nós
    No* anterior = nullptr;
    atual = listaNos->getCabeca();
    
    while (atual && atual != noParaRemover) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (anterior) {
        anterior->proximo = noParaRemover->proximo;
    } else {
        listaNos->setCabeca(noParaRemover->proximo);
    }

    ordem--;

    delete noParaRemover;
}

void GrafoLista::nova_aresta(int origem, int destino, int peso) {
    No* noOrigem = listaNos->getNo(origem);
    No* noDestino = listaNos->getNo(destino);
    
    if (!noOrigem || !noDestino) return;
    
    // Verificar se a aresta já existe
    if (existeAresta(origem, destino)) return;
    
    // Adiciona aresta origem -> destino
    Aresta* novaArestaOrigem = new Aresta(destino, peso);
    novaArestaOrigem->proxima = noOrigem->listaArestas;
    noOrigem->listaArestas = novaArestaOrigem;
    noOrigem->grau++;
    
    // Adiciona aresta destino -> origem (para grafos não direcionados)
    if (!direcionado) {
        if (!existeAresta(destino, origem)) { // Verifica se a aresta reversa já não existe
            Aresta* novaArestaDestino = new Aresta(origem, peso);
            novaArestaDestino->proxima = noDestino->listaArestas;
            noDestino->listaArestas = novaArestaDestino;
            noDestino->grau++;
        }
    }
}

void GrafoLista::deleta_aresta(int origem, int destino) {
    No* noOrigem = listaNos->getNo(origem);
    No* noDestino = listaNos->getNo(destino);
    
    if (!noOrigem) return;
    
    Aresta* arestaAtual = noOrigem->listaArestas;
    Aresta* anterior = nullptr;
    
    // Remover a aresta origem -> destino
    while (arestaAtual && arestaAtual->destino != destino) {
        anterior = arestaAtual;
        arestaAtual = arestaAtual->proxima;
    }
    
    if (arestaAtual) {
        if (anterior) {
            anterior->proxima = arestaAtual->proxima;
        } else {
            noOrigem->listaArestas = arestaAtual->proxima;
        }
        
        delete arestaAtual;
        noOrigem->grau--;
    }
    
    // Remover a aresta destino -> origem (se for grafo não direcionado)
    if (!direcionado && noDestino) {
        arestaAtual = listaNos->getAresta(destino, origem);
        anterior = nullptr;
        
        if (arestaAtual) {
            // Encontrar a aresta origem -> destino
            Aresta* temp = noDestino->listaArestas;
            while (temp && temp != arestaAtual) {
                anterior = temp;
                temp = temp->proxima;
            }
            
            if (anterior) {
                anterior->proxima = arestaAtual->proxima;
            } else {
                noDestino->listaArestas = arestaAtual->proxima;
            }
            
            delete arestaAtual;
            noDestino->grau--;
        }
    }
}

// Verifica se existe um nó específico
bool GrafoLista::existeNo(int id) {
    if(!listaNos->getNo(id))
        return false;
    return true;
}

// Verifica se existe uma aresta específica
bool GrafoLista::existeAresta(int origem, int destino) {
    if(!listaNos->getAresta(origem, destino)){
        return false;
    }

    return true;
}

// Retorna o Grau de um vértice
int GrafoLista::getGrau(int id) {
    No* no = listaNos->getNo(id);
    return (no != nullptr) ? no->grau : -1;
}

//Retorna um array com todos os vizinho de um nó
int* GrafoLista::getVizinhos(int id) {
    No* no = listaNos->getNo(id);
    if (!no) {
        return nullptr;
    }
    
    int* vizinhos = new int[no->grau];
    
    Aresta* aresta = no->listaArestas;
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

int GrafoLista::getPesoAresta(int origem, int destino) {
    Aresta* aresta = listaNos->getAresta(origem, destino);
    return (aresta != nullptr) ? aresta->peso : -1;
}

void GrafoLista::imprimeLista() {
    listaNos->imprimeLista();
}