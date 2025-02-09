#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "lista_encadeada.h"

class GrafoLista : public Grafo {
    private:
        ListaEncadeada* listaNos;
        
    public:
        GrafoLista();
        ~GrafoLista();
        
        void novo_no(int id, int peso) override;
        void deleta_no(int id) override;
        void nova_aresta(int origem, int destino, int peso) override;
        void deleta_aresta(int origem, int destino) override;
        
        bool existeNo(int id) override; // Verifica se existe um nó específico
        bool existeAresta(int origem, int destino) override; // Verifica se existe uma aresta específica
        int getGrau(int id) override; // Retorna o Grau de um vértice
        int* getVizinhos(int id) override; // Retorna um array com todos os vizinhos de um nó
        int getNumArestas() override; // Retorna o número de arestas do grafo
        int getPesoAresta(int origem, int destino) override; // Retorna o peso de uma aresta
        
        void imprimeLista() override; // Imprime o grafo na forma de lista encadeada
};

#endif
