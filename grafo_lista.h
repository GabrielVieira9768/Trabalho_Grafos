#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "lista_encadeada.h"

class GrafoLista : public Grafo {
    private:
        ListaEncadeada* listaNo;
        
    public:
        GrafoLista();
        ~GrafoLista();
        
        public void nova_aresta(int origem, int destino, int peso) override;
        public void deleta_aresta(int origem, int destino) override;
        public void novo_no(int id, int peso) override;
        public void deleta_no(int no) override;
};

#endif
