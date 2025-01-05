#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "lista_encadeada.h"

class GrafoLista : public Grafo {
    private:
        ListaEncadeada* listaAdj;
        int* pesosVertices;
        int* grauVertices;
        void dfs(int vertice, bool visitado[]);

    public:
        GrafoLista();
        ~GrafoLista();

        void inicializaLista(int ordem);
        void adicionaAresta(int origem, int destino, int peso);
        void carregaGrafo(const std::string& arquivo) override;
        //void imprimeGrafo();
        void dfsDetectaCiclo(int vertice, bool visitado[], int anterior, bool& cicloDetectado);
        void dfsArticulacao(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temArticulacao);
        void dfsPonte(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temPonte);

        bool eh_completo() override;
        bool eh_bipartido() override;
        int n_conexo() override;
        bool eh_arvore() override;
        bool possui_articulacao() override;
        bool possui_ponte() override;
};

#endif
