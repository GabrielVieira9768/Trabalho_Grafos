#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <iostream>

struct Aresta {
    int destino;
    int peso;
    Aresta* proxima;
    
    Aresta(int destino, int peso = 0);
};

struct No {
    int id;
    int peso;
    Aresta* listaArestas;
    No* proximo;
    
    No(int id, int peso = 0);
};

class ListaEncadeada {
private:
    No* cabeca;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    
    No* getNo(int id);
    Aresta* getAresta(int origem, int destino);
    void insereNo(int id, int peso);
    void removeNo(int id);
    void insereAresta(int destino, int peso);
    void removeAresta(int origem, int destino);
    void imprimeLista();
};

#endif