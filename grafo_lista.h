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
        
        int* getVizinhos(int id) override;
};

#endif
