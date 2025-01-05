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
        //void imprimeGrafo();
        void dfs_matriz(int v, bool visitado[]);
        bool eh_completo() override;
        bool eh_bipartido() override;
        bool eh_arvore() override;
        int n_conexo() override;
};

#endif
