#ifndef GRAFO_H
#define GRAFO_H

#include <string>

using namespace std;

class Grafo {
    protected: 
        int ordem = 0;
        bool direcionado;
        bool verticePonderado;
        bool arestaPonderada;
        string nomeArquivo;
        bool** arestasAdicionadas;
        
    public:
        virtual ~Grafo() {}
        
        void imprimeGrafo();
        int get_ordem();
        bool eh_direcionado();
        bool vertice_ponderado();
        bool aresta_ponderada();
        
        int get_grau();
        bool eh_completo();
        int n_conexo();
        
        void carrega_grafo(const string& arquivo);
        void DFS(int no, bool* visitado);
        void calculaMenorDistancia();
        void deleta_primeira_aresta(int id);
        void arvoreSteinerGuloso(int *vetTerminais, int tam, bool *marcados);
        void imprimeArvoreSteiner(int *vetTerminais, int tam);
        int* reconstruirCaminho(int destino, int* pai);
        int* encontraCaminhoMaisCurto(int origem, bool *marcados);
        bool existeCaminhoDFS(int atual, int destino, bool *visitado, bool *marcados);
        bool formaCiclo(int u, int v, bool *marcados);
        bool adicionaArestaSegura(int u, int v, bool *marcados);
        
        virtual void novo_no(int id, float peso);
        virtual void deleta_no(int no);
        virtual void nova_aresta(int origem, int destino, float peso);
        virtual void deleta_aresta(int origem, int destino);
        
        virtual bool existeNo(int id); // Verifica se existe um nó específico
        virtual bool existeAresta(int origem, int destino); // Verifica se existe uma aresta específica
        virtual int getGrau(int id); // Retorna o Grau de um vértice
        virtual int* getVizinhos(int id); // Retorna um array com todos os vizinhos de um nó
        virtual int getNumArestas(); // Retorna o número de arestas do grafo
        virtual float getPesoAresta(int origem, int destino); // Retorna o peso de uma aresta
        int getPai(int id);
        
        virtual void imprimeLista(); // Imprime o grafo na forma de lista encadeada
        virtual void imprimeMatriz(); // Imprime o grafo na forma de matriz
};

#endif