#include "./grafo_matriz.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

using namespace std;

GrafoMatriz::GrafoMatriz() : matrizAdj(nullptr), pesosVertices(nullptr) {}

GrafoMatriz::~GrafoMatriz() {
    if (matrizAdj) {
        for (int i = 0; i < ordem; i++) {
            delete[] matrizAdj[i];
        }
        delete[] matrizAdj;
    }
    delete[] pesosVertices;
}

void GrafoMatriz::novo_no(int id, float peso) {
    //listaNos->insereNo(id, peso);
}

void GrafoMatriz::deleta_no(int id) {
    //listaNos->removeNo(id);
}

void GrafoMatriz::nova_aresta(int origem, int destino, float peso) {
    // TO DO
}

void GrafoMatriz::deleta_aresta(int origem, int destino) {
    //listaNos->removeAresta(origem, destino);
}

// void GrafoMatriz::inicializaMatriz(int ordem) {
//     this->ordem = ordem;
//     matrizAdj = new int*[ordem];
//     for (int i = 0; i < ordem; i++) {
//         matrizAdj[i] = new int[ordem]();
//     }

//     if (verticePonderado) {
//         pesosVertices = new int[ordem]();
//     }
// }

// void GrafoMatriz::adicionaAresta(int origem, int destino, int peso) {
//     if(origem != destino){
//         matrizAdj[origem - 1][destino - 1] = peso;
//         if (!direcionado) {
//             matrizAdj[destino - 1][origem - 1] = peso;
//         }
//     }
// }

// void GrafoMatriz::carrega_grafo(const string& arquivo) {
//     nomeArquivo = arquivo;
//     ifstream entrada(arquivo.c_str());
//     if (!entrada.is_open()) {
//         cerr << "Erro ao abrir o arquivo." << endl;
//         return;
//     }

//     string linha;

//     // Lê a primeira linha com as configurações do grafo
//     if (getline(entrada, linha)) {
//         char* end;
//         ordem = strtol(linha.c_str(), &end, 10);
//         direcionado = (strtol(end, &end, 10) == 1);
//         verticePonderado = (strtol(end, &end, 10) == 1);
//         arestaPonderada = (strtol(end, &end, 10) == 1);
//     }

//     inicializaMatriz(ordem);

//     // Lê os pesos dos vértices, se houver
//     if (verticePonderado && getline(entrada, linha)) {
//         char* token = strtok(const_cast<char*>(linha.c_str()), " ");
//         for (int i = 0; i < ordem && token; i++) {
//             pesosVertices[i] = atoi(token);
//             token = strtok(nullptr, " ");
//         }
//     }

//     // Lê as arestas do grafo
//     while (getline(entrada, linha)) {
//         char* end;
//         int origem = strtol(linha.c_str(), &end, 10);
//         int destino = strtol(end, &end, 10);
//         int peso = arestaPonderada ? strtol(end, &end, 10) : 1;

//         adicionaAresta(origem, destino, peso);
//     }

//     entrada.close();
// }

// bool GrafoMatriz::eh_completo() {
//     for (int i = 0; i < ordem; ++i) {
//         for (int j = 0; j < ordem; ++j) {
//             if (i != j && matrizAdj[i][j] == 0) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// bool GrafoMatriz::eh_bipartido() {
//     if (ordem == 0) return true;

//     int totalSubsets = 1 << ordem;
//     for (int subset = 0; subset < totalSubsets; ++subset) {
//         bool* conjuntoA = new bool[ordem]();
//         bool* conjuntoB = new bool[ordem]();

//         for (int i = 0; i < ordem; ++i) {
//             if (subset & (1 << i)) {
//                 conjuntoA[i] = true;
//             } else {
//                 conjuntoB[i] = true;
//             }
//         }

//         bool bipartido = true;

//         // Verifica arestas dentro do conjunto A
//         for (int i = 0; i < ordem && bipartido; ++i) {
//             if (conjuntoA[i]) {
//                 for (int j = 0; j < ordem; ++j) {
//                     if (conjuntoA[j] && i != j && matrizAdj[i][j] != 0) {
//                         bipartido = false;
//                         break;
//                     }
//                 }
//             }
//         }

//         // Verifica arestas dentro do conjunto B
//         for (int i = 0; i < ordem && bipartido; ++i) {
//             if (conjuntoB[i]) {
//                 for (int j = 0; j < ordem; ++j) {
//                     if (conjuntoB[j] && i != j && matrizAdj[i][j] != 0) {
//                         bipartido = false;
//                         break;
//                     }
//                 }
//             }
//         }

//         delete[] conjuntoA;
//         delete[] conjuntoB;

//         if (bipartido) return true;
//     }

//     return false;
// }

// bool GrafoMatriz::eh_arvore() {
//     // Verificar se o número de arestas é igual a ordem - 1
//     int numArestas = 0;
//     for (int i = 0; i < ordem; i++) {
//         for (int j = i + 1; j < ordem; j++) {
//             if (matrizAdj[i][j] != 0) {
//                 numArestas++;
//             }
//         }
//     }

//     if (numArestas != ordem - 1) {
//         return false;
//     }

//     // Verificar se o grafo é conectado e não tem ciclos (usando DFS)
//     bool* visitado = new bool[ordem]();
//     int* pilha = new int[ordem];
//     int topo = -1;
//     int visitados = 0;

//     // Começamos a partir do vértice 0
//     pilha[++topo] = 0;
//     visitado[0] = true;
//     visitados++;

//     while (topo >= 0) {
//         int v = pilha[topo--];
        
//         for (int i = 0; i < ordem; i++) {
//             if (matrizAdj[v][i] != 0 && !visitado[i]) {
//                 pilha[++topo] = i;
//                 visitado[i] = true;
//                 visitados++;
//             }
//             else if (matrizAdj[v][i] != 0 && visitado[i]) {
//                 delete[] visitado;
//                 delete[] pilha;
//                 return false;
//             }
//         }
//     }

//     // Se todos os vértices foram visitados, o grafo é conectado
//     delete[] visitado;
//     delete[] pilha;
//     return visitados == ordem;
// }

// int GrafoMatriz::n_conexo() {
//     bool visitado[ordem];
//     std::fill(visitado, visitado + ordem, false);
//     int n_componentes = 0;

//     for (int i = 0; i < ordem; i++) {
//         if (!visitado[i]) {
//             n_componentes++;
//             dfs_matriz(i, visitado);
//         }
//     }

//     return n_componentes;
// }

// bool GrafoMatriz::possui_articulacao() {
//     int* tempoDescoberta = new int[ordem]();
//     int* low = new int[ordem]();
//     int* pai = new int[ordem];
//     bool* visitado = new bool[ordem]();
//     bool temArticulacao = false;

//     std::fill(pai, pai + ordem, -1);
//     int tempo = 0;

//     for (int i = 0; i < ordem; i++) {
//         if (!visitado[i]) {
//             dfsArticulacaoMatriz(i, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);
//         }
//     }

//     delete[] tempoDescoberta;
//     delete[] low;
//     delete[] pai;
//     delete[] visitado;

//     return temArticulacao;
// }

// int GrafoMatriz::get_grau() {
//     int maiorGrau = 0;

//     for (int v = 0; v < ordem; ++v) {
//         int grau = 0;

//         // Grau de saída
//         for (int i = 0; i < ordem; ++i) {
//             if (matrizAdj[v][i] != 0) {
//                 grau++;
//             }
//         }

//         // Grau de entrada (apenas para grafos direcionados)
//         if (direcionado) {
//             for (int i = 0; i < ordem; ++i) {
//                 if (matrizAdj[i][v] != 0) {
//                     grau++;
//                 }
//             }
//         }

//         if (grau > maiorGrau) {
//             maiorGrau = grau;
//         }
//     }

//     return maiorGrau;
// }

// void GrafoMatriz::novo_grafo(const std::string& arquivoEntrada, const std::string& arquivoSaida, int tentativas) {
//     const int MAX_TENTATIVAS = 5000;

//     if (tentativas >= MAX_TENTATIVAS) {
//         std::cerr << "Limite de tentativas atingido. Encerrando execução." << std::endl;
//         return;
//     }

//     // Abrir o arquivo de entrada
//     std::ifstream entrada(arquivoEntrada);
//     if (!entrada.is_open()) {
//         std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
//         return;
//     }

//     // Ler propriedades do arquivo de entrada
//     int grau, ordem, componenteConexa;
//     bool direcionado, verticePonderado, arestaPonderada, completo, bipartido, arvore, arestaPonte, verticeArticulacao;

//     entrada >> grau >> ordem >> direcionado >> componenteConexa
//             >> verticePonderado >> arestaPonderada >> completo >> bipartido
//             >> arvore >> arestaPonte >> verticeArticulacao;
//     entrada.close();

//     // Inicializar a matriz de adjacência
//     inicializaMatriz(ordem);

//     // Gerar pesos dos vértices aleatórios, se necessário
//     if (verticePonderado) {
//         for (int i = 0; i < ordem; ++i) {
//             pesosVertices[i] = rand() % 100 + 1;
//         }
//     }

//     // Gerar arestas aleatórias
//     int numArestas = rand() % (ordem * (ordem - 1) / 2) + 1;
//     for (int i = 0; i < numArestas; ++i) {
//         int origem = rand() % ordem + 1;
//         int destino = rand() % ordem + 1;
//         int peso = arestaPonderada ? rand() % 100 + 1 : 1;

//         if (origem != destino && matrizAdj[origem - 1][destino - 1] == 0) {
//             adicionaAresta(origem, destino, peso);
//         }
//     }

//     // Verificar propriedades do grafo gerado
//     bool condicoesAtendidas = true;
//     condicoesAtendidas &= (completo == eh_completo());
//     condicoesAtendidas &= (grau == get_grau());
//     condicoesAtendidas &= (bipartido == eh_bipartido());
//     condicoesAtendidas &= (arvore == eh_arvore());
//     condicoesAtendidas &= (arestaPonte == possui_ponte());
//     condicoesAtendidas &= (verticeArticulacao == possui_articulacao());
//     condicoesAtendidas &= (componenteConexa == n_conexo());

//     // Salvar o grafo no arquivo de saída
//     std::ofstream saida(arquivoSaida, std::ios::trunc);
//     if (!saida.is_open()) {
//         std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
//         return;
//     }

//     saida << ordem << " " << direcionado << " " << verticePonderado << " " << arestaPonderada << std::endl;

//     if (verticePonderado) {
//         for (int i = 0; i < ordem; ++i) {
//             saida << pesosVertices[i] << (i == ordem - 1 ? "\n" : " ");
//         }
//     }

//     for (int i = 0; i < ordem; ++i) {
//         for (int j = 0; j < ordem; ++j) {
//             if (matrizAdj[i][j] != 0) {
//                 saida << (i + 1) << " " << (j + 1) << " " << matrizAdj[i][j] << std::endl;
//             }
//         }
//     }
//     saida.close();

//     // Se as condições não foram atendidas, tente novamente
//     if (!condicoesAtendidas) {
//         novo_grafo(arquivoEntrada, arquivoSaida, tentativas + 1);
//     } else {
//         std::cout << "Grafo aleatório gerado e salvo em: " << arquivoSaida << std::endl;
//     }
// }


// //////////////////////------AUX------/////////////////////

// void GrafoMatriz::dfs_matriz(int v, bool visitado[]) {
//     visitado[v] = true;

//     for (int i = 0; i < ordem; ++i) {
//         if (matrizAdj[v][i] && !visitado[i]) {
//             dfs_matriz(i, visitado);
//         }
//     }
// }

// void GrafoMatriz::dfsArticulacaoMatriz(int v, bool* visitado, int* tempoDescoberta, int* low, int* pai, int& tempo, bool& temArticulacao) {
//     visitado[v] = true;
//     tempoDescoberta[v] = low[v] = ++tempo;
//     int filhos = 0;

//     for (int u = 0; u < ordem; ++u) {
//         if (matrizAdj[v][u]) {
//             if (!visitado[u]) {
//                 ++filhos;
//                 pai[u] = v;

//                 dfsArticulacaoMatriz(u, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);

//                 low[v] = std::min(low[v], low[u]);

//                 if ((pai[v] == -1 && filhos > 1) || (pai[v] != -1 && low[u] >= tempoDescoberta[v])) {
//                     temArticulacao = true;
//                 }
//             } else if (u != pai[v]) {
//                 low[v] = std::min(low[v], tempoDescoberta[u]);
//             }
//         }
//     }
// }

// bool GrafoMatriz::possui_ponte() {
//     auto tempoDescoberta = new int[ordem]();
//     auto low = new int[ordem]();
//     auto visitado = new bool[ordem]();
//     auto pai = new int[ordem];
//     std::fill(pai, pai + ordem, -1);

//     bool temPonte = false;
//     int tempo = 0;

//     for (int i = 0; i < ordem; ++i) {
//         if (!visitado[i]) {
//             dfsPonte(i, visitado, tempoDescoberta, low, pai, tempo, temPonte);
//         }
//     }

//     delete[] tempoDescoberta;
//     delete[] low;
//     delete[] visitado;
//     delete[] pai;

//     return temPonte;
// }

// void GrafoMatriz::dfsPonte(int v, bool* visitado, int* tempoDescoberta, int* low, int* pai, int& tempo, bool& temPonte) {
//     visitado[v] = true;
//     tempoDescoberta[v] = low[v] = ++tempo;

//     for (int u = 0; u < ordem; ++u) {
//         if (matrizAdj[v][u]) {
//             if (!visitado[u]) {
//                 pai[u] = v;

//                 dfsPonte(u, visitado, tempoDescoberta, low, pai, tempo, temPonte);

//                 low[v] = std::min(low[v], low[u]);

//                 if (low[u] > tempoDescoberta[v]) {
//                     temPonte = true;
//                 }
//             } else if (u != pai[v]) {
//                 low[v] = std::min(low[v], tempoDescoberta[u]);
//             }
//         }
//     }
// }
