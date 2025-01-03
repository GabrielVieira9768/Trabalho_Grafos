#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"

using namespace std;

class GrafoMatriz : public Grafo {
    public:
        bool eh_bipartido() override;
};

#endif // GRAFOMATRIZ_H