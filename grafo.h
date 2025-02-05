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
        
        int get_grau();
        bool eh_completo();
        /*bool eh_bipartido();
        int n_conexo();
        bool eh_arvore();
        bool possui_articulacao();
        bool possui_ponte();
        void novo_grafo(const string& arquivoEntrada, const string& arquivoSaida, int tentativas = 0);*/
        
        void carrega_grafo(const string& arquivo);
        
        int menor_distancia(int origem, int destino);
        virtual void novo_no(int id, int peso);
        virtual void deleta_no(int no);
        virtual void nova_aresta(int origem, int destino, int peso);
        virtual void deleta_aresta(int origem, int destino);
        
        virtual bool existeNo(int id); // Verifica se existe um nó específico
        virtual bool existeAresta(int origem, int destino); // Verifica se existe uma aresta específica
        virtual int getGrau(int id); // Retorna o Grau de um vértice
        virtual int* getVizinhos(int id); // Retorna um array com todos os vizinhos de um nó
        virtual int getNumArestas(); // Retorna o número de arestas do grafo
};

#endif