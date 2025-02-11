#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

using namespace std;

class GrafoMatriz : public Grafo {
    private:
        int** matrizAdj;
        int* pesosVertices;

        void inicializaMatriz(int ordem);

    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void novo_no(int id, float peso) override;
        void deleta_no(int id) override;
        void nova_aresta(int origem, int destino, float peso) override;
        void deleta_aresta(int origem, int destino) override;

};

#endif
