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
        
        bool eh_bipartido();
        int n_conexo();
        int get_grau();
        bool eh_completo();
        bool eh_arvore();
        bool possui_articulacao();
        bool possui_ponte();
        void carrega_grafo(const string& arquivo);
        void novo_grafo(const string& arquivoEntrada, const string& arquivoSaida, int tentativas = 0);
        
        virtual void nova_aresta(int origem, int destino, int peso);
        virtual void deleta_aresta(int origem, int destino);
        virtual void novo_no();
        virtual void deleta_no(int no);
        int menor_distancia(int origem, int destino);
};

#endif