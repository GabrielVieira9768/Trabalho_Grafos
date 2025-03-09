#include "./grafo_lista.h"

using namespace std;

GrafoLista::GrafoLista() {
    listaNos = new ListaEncadeada();
}

GrafoLista::~GrafoLista() {
    delete listaNos;
}

void GrafoLista::novo_no(int id, float peso) {
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
            if (!direcionado) { // Remove a aresta reversa em grafos não direcionados
                deleta_aresta(id, atual->id);
            }
        }
        atual = atual->proximo;
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

    cout << "Excluindo nó " << id << "..." << endl;

    ordem--;

    // Chama o destruidor do nó, que vai limpar as arestas associadas e deletar o nó
    delete noParaRemover;
}

void GrafoLista::nova_aresta(int origem, int destino, float peso) {
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
    
    if (!noOrigem || !noDestino) return;
    
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
    No* no = listaNos->getNo(id); // Obtém o nó com o ID especificado
    if (!no) {
        return -1; // Retorna -1 se o nó não existir
    }

    // Grau de saída (número de arestas na lista de adjacência do nó)
    int grauSaida = no->grau;

    // Se o grafo for direcionado, calcula o grau de entrada
    if (direcionado) {
        int grauEntrada = 0;
        No* atual = listaNos->getCabeca();

        // Percorre todos os nós para contar as arestas que apontam para o nó atual
        while (atual) {
            Aresta* arestaAtual = atual->listaArestas;
            while (arestaAtual) {
                if (arestaAtual->destino == id) {
                    grauEntrada++;
                }
                arestaAtual = arestaAtual->proxima;
            }
            atual = atual->proximo;
        }

        return grauSaida + grauEntrada; // Retorna o grau total (saída + entrada)
    }

    return grauSaida; // Retorna o grau de saída (grafo não direcionado)
}

//Retorna um array com todos os vizinho de um nó
int* GrafoLista::getVizinhos(int id) {
    No* no = listaNos->getNo(id); // Obtém o nó com o ID especificado
    if (!no) {
        return nullptr; // Retorna nullptr se o nó não existir
    }

    // Conta o número de vizinhos
    int count = 0;
    Aresta* arestaAtual = no->listaArestas;
    while (arestaAtual) {
        count++;
        arestaAtual = arestaAtual->proxima;
    }

    // Aloca um array para armazenar os vizinhos
    int* vizinhos = new int[count];
    arestaAtual = no->listaArestas;
    int index = 0;

    // Preenche o array com os IDs dos vizinhos
    while (arestaAtual) {
        vizinhos[index++] = arestaAtual->destino;
        arestaAtual = arestaAtual->proxima;
    }

    return vizinhos; // Retorna o array de vizinhos
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

float GrafoLista::getPesoAresta(int origem, int destino) {
    Aresta* aresta = listaNos->getAresta(origem, destino);
    return (aresta != nullptr) ? aresta->peso : -1;
}

void GrafoLista::imprimeLista() {
    listaNos->imprimeLista();
}