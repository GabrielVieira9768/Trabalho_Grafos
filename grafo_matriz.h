#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include <vector>

using namespace std;

class GrafoMatriz : public Grafo {
    private:
        int numero_vertices;
        vector<vector<int>> matriz;
};

#endif // GRAFOMATRIZ_H