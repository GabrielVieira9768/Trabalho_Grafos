#include "grafo_lista.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

using namespace std;

GrafoLista::GrafoLista() : listaAdj(nullptr), pesosVertices(nullptr), grauVertices(nullptr) {}

GrafoLista::~GrafoLista() {
    if (listaAdj) {
        delete[] listaAdj; // Liberar o array alocado com new[]
    }

    if (pesosVertices) {
        delete[] pesosVertices; // Liberar o array alocado com new[]
    }

    if (grauVertices) {
        delete[] grauVertices; // Liberar o array alocado com new[]
    }
}

void GrafoLista::inicializaLista(int ordem) {
    this->ordem = ordem;

    // Alocar o array de ListaEncadeada com new[]
    listaAdj = new ListaEncadeada[ordem];

    // Alocar arrays para pesos e graus (se necessário)
    if (verticePonderado) {
        pesosVertices = new int[ordem](); // Inicializar com zero
    }

    grauVertices = new int[ordem](); // Inicializar com zero
}

void GrafoLista::adicionaAresta(int origem, int destino, int peso) {
    if(origem != destino){
        listaAdj[origem - 1].insereNo(destino, peso);
        grauVertices[origem - 1]++;
        grauVertices[destino - 1]++;

        if (!direcionado) {
            listaAdj[destino - 1].insereNo(origem, peso);
        }
    }
}


void GrafoLista::carrega_grafo(const string& arquivo) {
    nomeArquivo = arquivo;
    ifstream entrada(arquivo.c_str());
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string linha;

    // Lê a primeira linha com as configurações do grafo
    if (getline(entrada, linha)) {
        char* end;
        ordem = strtol(linha.c_str(), &end, 10);
        direcionado = (strtol(end, &end, 10) == 1);
        verticePonderado = (strtol(end, &end, 10) == 1);
        arestaPonderada = (strtol(end, &end, 10) == 1);
    }

    inicializaLista(ordem);

    // Lê os pesos dos vértices, se houver
    if (verticePonderado && getline(entrada, linha)) {
        char* token = strtok(const_cast<char*>(linha.c_str()), " ");
        for (int i = 0; i < ordem && token; i++) {
            pesosVertices[i] = atoi(token);
            token = strtok(nullptr, " ");
        }
    }

    // Lê as arestas do grafo
    while (getline(entrada, linha)) {
        char* end;
        int origem = strtol(linha.c_str(), &end, 10);
        int destino = strtol(end, &end, 10);
        int peso = arestaPonderada ? strtol(end, &end, 10) : 1;

        adicionaAresta(origem, destino, peso);
    }

    entrada.close();
}

// void GrafoLista::imprimeGrafo() {
//     cout << "Lista de Adjacência:" << endl;
//     for (int i = 0; i < ordem; i++) {
//         cout << i + 1 << ": ";
//         listaAdj[i].imprimeLista();
//         cout << endl;
//     }

//     if (verticePonderado) {
//         cout << "Pesos dos Vértices:" << endl;
//         for (int i = 0; i < ordem; i++) {
//             cout << pesosVertices[i] << " ";
//         }
//         cout << endl;
//     }

//     cout << "Graus dos Vértices:" << endl;
//     for (int i = 0; i < ordem; i++) {
//         cout << "Vértice " << i + 1 << ": " << grauVertices[i] << endl;
//     }
// }

bool GrafoLista::eh_completo(){
    for (int i = 0; i < this->ordem; i++) {
        if(this->ordem -1 != this->grauVertices[i])
            return false;
    }

    return true;
}

bool GrafoLista::eh_bipartido() {
    int n = this->ordem;
    int total = 1 << n; 

    // Percorre todas as divisões possíveis dos vértices em dois conjuntos
    for (int mask = 0; mask < total; ++mask) {
        bool valido = true;

        // Verifica todas as arestas
        for (int v = 0; v < n && valido; ++v) {
            No* no = listaAdj[v].getCabeca();
            while (no != nullptr) {
                int destino = no->destino - 1; // Ajusta índice para base 0

                // Checa se ambos os vértices da aresta estão no mesmo conjunto
                if (((mask >> v) & 1) == ((mask >> destino) & 1)) {
                    valido = false;
                    break;
                }
                no = no->prox;
            }
        }

        // Se encontramos uma divisão válida, o grafo é bipartido
        if (valido) return true;
    }

    // Se nenhuma divisão válida foi encontrada, o grafo não é bipartido
    return false;
}


int GrafoLista::n_conexo() {
    bool visitado[ordem];
    std::fill(visitado, visitado + ordem, false);
    int n_componentes = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            n_componentes++;
            dfs(i, visitado);
        }
    }

    return n_componentes;
}

bool GrafoLista::eh_arvore() {
    bool* marcados = new bool[ordem];
    std::fill(marcados, marcados + ordem, false);
    
    if (n_conexo() != 1) {
        delete[] marcados;
        return false;
    }
    
    bool existeCiclo = false;
    dfsDetectaCiclo(0, marcados, -1, existeCiclo);
    
    delete[] marcados;
    return !existeCiclo;
}

bool GrafoLista::possui_articulacao() {
    int* tempoDescoberta = new int[ordem]();
    int* low = new int[ordem]();
    int* pai = new int[ordem];
    bool* visitado = new bool[ordem]();
    bool temArticulacao = false;

    std::fill(pai, pai + ordem, -1);
    int tempo = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            dfsArticulacao(i, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);
        }
    }

    delete[] tempoDescoberta;
    delete[] low;
    delete[] pai;
    delete[] visitado;

    return temArticulacao;
}

bool GrafoLista::possui_ponte() {
    int* tempoDescoberta = new int[ordem]();
    int* low = new int[ordem]();
    int* pai = new int[ordem];
    bool* visitado = new bool[ordem]();
    bool temPonte = false;

    std::fill(pai, pai + ordem, -1);
    int tempo = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            dfsPonte(i, visitado, tempoDescoberta, low, pai, tempo, temPonte);
        }
    }

    delete[] tempoDescoberta;
    delete[] low;
    delete[] pai;
    delete[] visitado;

    return temPonte;
}

int GrafoLista::get_grau() {
    if (ordem == 0) {
        cerr << "O grafo está vazio." << endl;
        return -1; // Retorna -1 para indicar erro
    }

    int maiorGrau = grauVertices[0];

    for (int i = 0; i < ordem; i++) {
        if (grauVertices[i] > maiorGrau) {
            maiorGrau = grauVertices[i];
        }
    }

    return maiorGrau;
}

//////////////////////------AUX------/////////////////////

void GrafoLista::dfsPonte(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temPonte) {
    visitado[u] = true;
    tempoDescoberta[u] = low[u] = ++tempo;

    No* no = listaAdj[u].getCabeca();
    while (no != nullptr) {
        int v = no->destino - 1;

        if (!visitado[v]) {
            pai[v] = u;
            dfsPonte(v, visitado, tempoDescoberta, low, pai, tempo, temPonte);

            low[u] = std::min(low[u], low[v]);

            if (low[v] > tempoDescoberta[u]) {
                temPonte = true;
            }
        } else if (v != pai[u]) {
            low[u] = std::min(low[u], tempoDescoberta[v]);
        }

        no = no->prox;
    }
}
// Método para auxiliar para dectectar clicos
void GrafoLista::dfsDetectaCiclo(int noAtual, bool marcados[], int pai, bool& existeCiclo) {
    if (existeCiclo) return;
    
    marcados[noAtual] = true;
    
    No* vizinho = listaAdj[noAtual].getCabeca();
    while (vizinho != nullptr) {
        int vizinhoDestino = vizinho->destino - 1;
        if (!marcados[vizinhoDestino]) {
            dfsDetectaCiclo(vizinhoDestino, marcados, noAtual, existeCiclo); 
        } else if (vizinhoDestino != pai) {
            existeCiclo = true;
            return;
        }
        vizinho = vizinho->prox;
    }
}

// Método para auxiliar na busca pelas componentes conexas
void GrafoLista::dfs(int vertice, bool visitado[]) {
    visitado[vertice] = true;
    No* no = listaAdj[vertice].getCabeca();
    while (no) {
        int adj = no->destino - 1;
        if (!visitado[adj]) {
            dfs(adj, visitado);
        }
        no = no->prox;
    }
}

void GrafoLista::dfsArticulacao(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temArticulacao) {
    visitado[u] = true;
    tempoDescoberta[u] = low[u] = ++tempo;
    int filhos = 0;

    No* no = listaAdj[u].getCabeca();
    while (no != nullptr) {
        int v = no->destino - 1;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;
            dfsArticulacao(v, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);

            low[u] = std::min(low[u], low[v]);

            if ((pai[u] == -1 && filhos > 1) || (pai[u] != -1 && low[v] >= tempoDescoberta[u])) {
                temArticulacao = true;
            }
        } else if (v != pai[u]) {
            low[u] = std::min(low[u], tempoDescoberta[v]);
        }

        no = no->prox;
    }
}