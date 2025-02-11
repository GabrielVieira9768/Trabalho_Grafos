#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

using namespace std;

class GrafoMatriz : public Grafo {
    private:
        float** matrizAdj;
        float* pesosVertices;
        int capacidade;

        void redimensionarMatriz(); // Função para redimensionar a matriz

    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void novo_no(int id, float peso) override;
        void deleta_no(int id) override;
        void nova_aresta(int origem, int destino, float peso) override;
        void deleta_aresta(int origem, int destino) override;

        bool existeAresta(int origem, int destino) override;
        float getPesoAresta(int origem, int destino) override;
        int* getVizinhos(int id) override;
        int getGrau(int id) override;

        void imprimeMatriz();
};

#endif
