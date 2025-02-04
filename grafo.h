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
        
        int get_ordem();
        bool eh_direcionado();
        bool vertice_ponderado();
        bool aresta_ponderada();
        void imprimeGrafo();
        
        /*bool eh_bipartido();
        int n_conexo();
        int get_grau();
        bool eh_completo();
        bool eh_arvore();
        bool possui_articulacao();
        bool possui_ponte();
        void novo_grafo(const string& arquivoEntrada, const string& arquivoSaida, int tentativas = 0);*/
        
        void carrega_grafo(const string& arquivo);
        virtual void novo_no(int id, int peso);
        virtual void deleta_no(int no);
        virtual void nova_aresta(int origem, int destino, int peso);
        virtual void deleta_aresta(int origem, int destino);
        int menor_distancia(int origem, int destino);
        
};

#endif