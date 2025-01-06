#ifndef GRAFO_H
#define GRAFO_H

#include <string>

using namespace std;

class Grafo {
    protected:
        int ordem;
        bool direcionado;
        bool verticePonderado;
        bool arestaPonderada;
        string nomeArquivo;

    public:
        virtual ~Grafo() {}

        void imprimeGrafo();
        int get_ordem();
        bool eh_direcionado();
        bool vertice_ponderado();
        bool aresta_ponderada();
        
        virtual bool eh_bipartido();
        virtual int n_conexo();
        virtual int get_grau();
        virtual bool eh_completo();
        virtual bool eh_arvore();
        virtual bool possui_articulacao();
        virtual bool possui_ponte();
        virtual void carrega_grafo(const string& arquivo);
};

#endif