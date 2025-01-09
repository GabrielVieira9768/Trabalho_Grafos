#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

class GrafoMatriz : public Grafo {
    private:
        int** matrizAdj;
        int* pesosVertices;

        void inicializaMatriz(int ordem);
        void adicionaAresta(int origem, int destino, int peso);
        void dfs_matriz(int v, bool visitado[]);
        void dfsPonte(int v, bool* visitado, int* tempoDescoberta, int* low, int* pai, int& tempo, bool& temPonte);
        void dfsArticulacaoMatriz(int v, bool *visitado, int *tempoDescoberta, int *low, int *pai, int &tempo, bool &temArticulacao);

    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void novo_grafo(const std::string &arquivoEntrada, const std::string &arquivoSaida, int tentativas) override;
        void construirArvore(int ordem);
        void construirGrafoCompleto(int ordem, bool arestaPonderada);
        void construirGrafoConexo(int ordem, int componentes, bool arestaPonderada);
        void salvarGrafo(const std::string &arquivoSaida, int ordem, bool direcionado, bool verticePonderado, bool arestaPonderada);
        void carrega_grafo(const std::string &arquivo) override;
        bool eh_completo() override;
        bool eh_bipartido() override;
        bool eh_arvore() override;
        int n_conexo() override;
        bool possui_articulacao() override;
        int get_grau() override;
        bool possui_ponte() override;

};

#endif
