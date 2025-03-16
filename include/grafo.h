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

    public:
        virtual ~Grafo() {}
        
        void imprimeGrafo();            //Autores: Carlos, Gabriel, Maria, Vítor. Imprime informações do grafo
        int get_ordem();                //Autor: Gabriel. Retorna a ordem do grafo
        bool eh_direcionado();          //Autor: Gabriel. Retorna se o grafo é direcionado
        bool vertice_ponderado();       //Autor: Gabriel. Retorna se o grafo tem vértices ponderados
        bool aresta_ponderada();        //Autor: Gabriel. Retorna se o grafo tem arestas ponderadas
        
        int get_grau();                 //Autores: Carlos, Gabriel, Maria. Retorna o grau do grafo
        bool eh_completo();             //Autores: Carlos, Gabriel. Verifica se o grafo é completo
        int n_conexo();                 //Autores: Carlos, Gabriel, Maria. Retorna o número de componentes conexas
        
        void carrega_grafo(const string& arquivo);      //Autora: Maria. Carrega o grafo a partir de um arquivo
        void DFS(int no, bool* visitado);               //Autores: Carlos, Gabriel, Maria.. Algoritmo de busca em profundidade   
        void calculaMenorDistancia();                   //Autora: Maria. Calcula a menor distância entre dois vértices    
        void deleta_primeira_aresta(int id);            //Autora: Maria. Deleta a primeira aresta de um nó
        void steinerTree(int *terminais, int tamanho, bool randomizado = false, float alpha = 0.3 , bool reativo = false); //Autores: Carlos, Gabriel, Maria, Vítor. Algoritmo de Steiner Tree
        int* geraTerminaisAleatorios(int ordem, int& tamanhoTerminais); //Autor: Vítor. Gera terminais aleatórios
        
        virtual void novo_no(int id, float peso);                       //Autores: Carlos, Gabriel. Adiciona um novo nó ao grafo
        virtual void deleta_no(int no);                                 //Autores: Carlos, Gabriel. Deleta um nó do grafo
        virtual void nova_aresta(int origem, int destino, float peso);  //Autores: Carlos, Gabriel. Adiciona uma nova aresta ao grafo
        virtual void deleta_aresta(int origem, int destino);            //Autores: Carlos, Gabriel. Deleta uma aresta do grafo
        
        virtual bool existeNo(int id);                          //Autor: Gabriel. Verifica se um nó existe
        virtual bool existeAresta(int origem, int destino);     //Autor: Gabriel. Verifica se uma aresta existe
        virtual int getGrau(int id);                            //Autores: Gabriel e Maria. Retorna o grau de um nó       
        virtual int* getVizinhos(int id);                       //Autores: Gabriel, Carlos. Retorna os vizinhos de um nó
        virtual int getNumArestas();                            //Autor: Gabriel. Retorna o número de arestas do grafo
        virtual float getPesoAresta(int origem, int destino);   //Autor: Gabriel. Retorna o peso de uma aresta
        
        virtual void imprimeLista();                            //Autor: Gabriel. Imprime o grafo na forma de lista encadeada 
        virtual void imprimeMatriz();                           //Autor: Gabriel. Imprime o grafo na forma de matriz de adjacência
};

#endif