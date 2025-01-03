#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "grafo.h"

class GrafoLista : public Grafo {
    private:     

    public:
        GrafoLista(int n);
        ~GrafoLista();

        bool eh_bipartido() override;
        int n_conexo() override;
};

#endif