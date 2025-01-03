#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"

class GrafoMatriz : public Grafo {
    private:
        int numero_vertices;

    public:
        bool eh_bipartido() override;
};

#endif // GRAFOMATRIZ_H