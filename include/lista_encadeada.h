#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <iostream>

struct Aresta {
    int destino;
    float peso;
    Aresta* proxima;
    
    Aresta(int destino, float peso = 0);
};

struct No {
    int id;
    float peso;
    int grau;
    Aresta* listaArestas;
    No* proximo;
    
    No(int id, float peso = 0);
};

class ListaEncadeada {
private:
    No* cabeca;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    
    No* getNo(int id);
    Aresta* getAresta(int origem, int destino);
    void setCabeca(No* novoCabeca);
    void imprimeLista();
    No* getCabeca(); 
};

#endif