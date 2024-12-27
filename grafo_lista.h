#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"

class GrafoLista : public Grafo {
    private:
        struct No {
            int vertice;
            No* prox;
        };

        int numero_vertices;
        No** lista_adj;

    public:
        GrafoLista(int n);
        ~GrafoLista();

        void adicionarAresta(int u, int v);

        bool eh_bipartido() override;
        int n_conexo() override;
};

#endif // GRAFOLISTA_H