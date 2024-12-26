#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <vector>

class GrafoMatriz : public Grafo {
    private:
        int num_vertices;
        std::vector<std::vector<int>> matriz;
};

#endif // GRAFOMATRIZ_H