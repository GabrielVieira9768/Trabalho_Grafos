#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "lista_encadeada.h"

class GrafoLista : public Grafo {
    private:
        ListaEncadeada* listaAdj;
        int* pesosVertices;
        int* grauVertices;

    public:
        GrafoLista();
        ~GrafoLista();

        void inicializaLista(int ordem);
        void adicionaAresta(int origem, int destino, int peso);
        void carregaGrafo(const std::string& arquivo) override;
        void imprimeGrafo();

        bool eh_completo() override;
};

#endif
