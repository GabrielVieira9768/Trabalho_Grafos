#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

using namespace std;

class GrafoMatriz : public Grafo {
    private:
        int** matrizAdj;
        int* pesosVertices;
        int capacidade;

        void inicializaMatriz(int ordem);
        void redimensionarMatriz(); // Função para redimensionar a matriz

    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void novo_no(int id, float peso) override;
        void deleta_no(int id) override;
        void nova_aresta(int origem, int destino, float peso) override;
        void deleta_aresta(int origem, int destino) override;

        bool existeAresta(int origem, int destino) override;
        int getPesoAresta(int origem, int destino) override;

        void imprimeMatriz();
};

#endif
