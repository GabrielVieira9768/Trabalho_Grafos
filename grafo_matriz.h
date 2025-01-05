#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

class GrafoMatriz : public Grafo {
    private:
        int** matrizAdj;
        int* pesosVertices;

    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void inicializaMatriz(int ordem);
        void adicionaAresta(int origem, int destino, int peso);
        void carregaGrafo(const std::string& arquivo) override;
        void imprimeGrafo();
        bool eh_completo() override;
        bool eh_bipartido() override;
};

#endif
