#include "grafo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int Grafo::get_ordem() {
    return this->ordem;
}

bool Grafo::eh_direcionado() {
    return this->direcionado;
}

bool Grafo::vertice_ponderado() {
    return this->verticePonderado;
}

bool Grafo::aresta_ponderada() {
    return this->arestaPonderada;
}

void Grafo::novo_no(int id, int peso) {
    cerr << "Método novo_no chamado na classe base" << endl;
}

void Grafo::deleta_no(int id) {
    cerr << "Método deleta_no chamado na classe base" << endl;
}

void Grafo::nova_aresta(int origem, int destino, int peso) {
    cerr << "Método nova_aresta chamado na classe base"<< endl;
}

void Grafo::deleta_aresta(int origem, int destino) {
    cerr << "Método deleta_aresta chamado na classe base" << endl;
}

bool Grafo::existeNo(int id) {
  return false;
}

bool Grafo::existeAresta(int origem, int destino) {
  return false;
}

int* Grafo::getVizinhos(int id) {
    return 0;
}

int Grafo::getGrau(int id) {
  return 0;
}

int Grafo::getNumArestas() {
  return 0;
}

int Grafo::get_grau() {
  int maiorGrau = 0;
  
  for(int i = 1; i <= ordem; i++) {
      if(getGrau(i) > maiorGrau) {
          maiorGrau = getGrau(i);
      }
  }
  
  return maiorGrau;
}

bool Grafo::eh_completo() {
    for (int i = 1; i <= ordem; i++) {
        if (getGrau(i) != ordem - 1) { // Verifica se cada nó tem grau igual (ordem - 1)
            return false;
        }
    }
    
    return true;
}

int Grafo::n_conexo() {
    // Aloca um array para marcar os nós visitados
    bool* visitado = new bool[ordem + 1]; // +1 porque os nós começam de 1
    for (int i = 1; i <= ordem; i++) {
        visitado[i] = false;
    }

    int contador = 0;

    // Percorre todos os nós do grafo
    for (int i = 1; i <= ordem; i++) {
        if (!visitado[i]) {
            // Se o nó não foi visitado, inicia uma DFS a partir dele
            DFS(i, visitado);
            contador++; // Incrementa o contador de componentes conexos
        }
    }

    // Libera a memória alocada para o array de visitados
    delete[] visitado;

    return contador;
}

void Grafo::DFS(int no, bool* visitado) {
    // Marca o nó como visitado
    visitado[no] = true;

    // Obtém os vizinhos do nó
    int* vizinhos = getVizinhos(no);

    // Se o nó tiver vizinhos, percorre cada um deles
    if (vizinhos) {
        for (int i = 0; i < getGrau(no); i++) {
            int vizinho = vizinhos[i];
            if (!visitado[vizinho]) {
                // Se o vizinho não foi visitado, realiza uma DFS a partir dele
                DFS(vizinho, visitado);
            }
        }

        // Libera a memória alocada para o array de vizinhos
        delete[] vizinhos;
    }
}

bool Grafo::eh_arvore() {
    // Verifica se o número de arestas é igual a (ordem - 1)
    if (getNumArestas() != ordem - 1) {
        return false;
    }

    // Verifica se o grafo é conexo
    bool* visitado = new bool[ordem + 1]; // +1 porque os nós começam de 1
    for (int i = 1; i <= ordem; i++) {
        visitado[i] = false;
    }

    // Realiza uma DFS para verificar conexidade e ausência de ciclos
    bool temCiclo = DFS_verificaCiclo(1, -1, visitado);

    // Verifica se todos os nós foram visitados (grafo conexo)
    bool conexo = true;
    for (int i = 1; i <= ordem; i++) {
        if (!visitado[i]) {
            conexo = false;
            break;
        }
    }

    // Libera a memória alocada para o array de visitados
    delete[] visitado;

    // O grafo é uma árvore se for conexo e não tiver ciclos
    return conexo && !temCiclo;
}

bool Grafo::DFS_verificaCiclo(int no, int pai, bool* visitado) {
    visitado[no] = true;

    // Obtém os vizinhos do nó
    int* vizinhos = getVizinhos(no);

    // Se o nó tiver vizinhos, percorre cada um deles
    if (vizinhos) {
        for (int i = 0; i < getGrau(no); i++) {
            int vizinho = vizinhos[i];

            if (!visitado[vizinho]) {
                // Se o vizinho não foi visitado, realiza uma DFS a partir dele
                if (DFS_verificaCiclo(vizinho, no, visitado)) {
                    // Se encontrou um ciclo, retorna true
                    delete[] vizinhos;
                    return true;
                }
            } else if (vizinho != pai) {
                // Se o vizinho já foi visitado e não é o pai, há um ciclo
                delete[] vizinhos;
                return true;
            }
        }

        // Libera a memória alocada para o array de vizinhos
        delete[] vizinhos;
    }

    // Não encontrou ciclos
    return false;
}

// bool Grafo::possui_ponte() {
//     // Aloca arrays para armazenar o tempo de descoberta e o menor tempo alcançável
//     int* tempoDescoberta = new int[ordem + 1]; // +1 porque os nós começam de 1
//     int* menorTempo = new int[ordem + 1];
//     bool* visitado = new bool[ordem + 1];

//     // Inicializa os arrays
//     for (int i = 1; i <= ordem; i++) {
//         visitado[i] = false;
//         tempoDescoberta[i] = -1;
//         menorTempo[i] = -1;
//     }

//     // Variável para armazenar o tempo de descoberta atual
//     int tempo = 0;

//     // Realiza a DFS para cada nó não visitado
//     for (int i = 1; i <= ordem; i++) {
//         if (!visitado[i]) {
//             if (DFS_verificaPonte(i, -1, tempo, tempoDescoberta, menorTempo, visitado)) {
//                 // Se encontrou uma ponte, libera a memória e retorna true
//                 delete[] tempoDescoberta;
//                 delete[] menorTempo;
//                 delete[] visitado;
//                 return true;
//             }
//         }
//     }

//     // Libera a memória alocada
//     delete[] tempoDescoberta;
//     delete[] menorTempo;
//     delete[] visitado;

//     // Se não encontrou pontes, retorna false
//     return false;
// }

// bool Grafo::DFS_verificaPonte(int no, int pai, int& tempo, int* tempoDescoberta, int* menorTempo, bool* visitado) {
//     // Marca o nó como visitado e define o tempo de descoberta e o menor tempo alcançável
//     visitado[no] = true;
//     tempoDescoberta[no] = menorTempo[no] = ++tempo;

//     // Obtém os vizinhos do nó
//     int* vizinhos = getVizinhos(no);

//     // Se o nó tiver vizinhos, percorre cada um deles
//     if (vizinhos) {
//         for (int i = 0; i < getGrau(no); i++) {
//             int vizinho = vizinhos[i];

//             if (!visitado[vizinho]) {
//                 // Se o vizinho não foi visitado, realiza uma DFS a partir dele
//                 if (DFS_verificaPonte(vizinho, no, tempo, tempoDescoberta, menorTempo, visitado)) {
//                     // Se encontrou uma ponte, retorna true
//                     delete[] vizinhos;
//                     return true;
//                 }

//                 // Atualiza o menor tempo alcançável do nó atual
//                 menorTempo[no] = min(menorTempo[no], menorTempo[vizinho]);

//                 // Verifica se a aresta (no, vizinho) é uma ponte
//                 if (menorTempo[vizinho] > tempoDescoberta[no]) {
//                     delete[] vizinhos;
//                     return true;
//                 }
//             } else if (vizinho != pai) {
//                 // Se o vizinho já foi visitado e não é o pai, atualiza o menor tempo alcançável
//                 menorTempo[no] = min(menorTempo[no], tempoDescoberta[vizinho]);
//             }
//         }

//         // Libera a memória alocada para o array de vizinhos
//         delete[] vizinhos;
//     }

//     // Não encontrou pontes
//     return false;
// }

void Grafo::carrega_grafo(const string& arquivo) {
    ifstream file(arquivo.c_str());
    
    if (!file) {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
        exit(EXIT_FAILURE);
    }
    
    string linha;
    int ordem_int;
    
    // Lê a descrição do grafo
    if (getline(file, linha)) {
        int direcionado_int, verticePonderado_int, arestaPonderada_int;
        sscanf(linha.c_str(), "%d %d %d %d", &ordem_int, &direcionado_int, &verticePonderado_int, &arestaPonderada_int);
        direcionado = direcionado_int;
        verticePonderado = verticePonderado_int;
        arestaPonderada = arestaPonderada_int;
    }
    
    // Lê os pesos dos nós se ponderado
    if (verticePonderado && getline(file, linha)) {
        int peso;
        for (int id = 1; id <= ordem_int; ++id) {
            size_t pos = linha.find(" ");
            if (pos != string::npos) {
                peso = atoi(linha.substr(0, pos).c_str());
                linha = linha.substr(pos + 1);
            } else {
                peso = atoi(linha.c_str());
            }
            novo_no(id, peso);
        }
    }
    
    // Lê as arestas
    while (getline(file, linha)) {
        if (linha.empty()) continue;
        
        int origem, destino, peso = 0;
        if (arestaPonderada) {
            sscanf(linha.c_str(), "%d %d %d", &origem, &destino, &peso);
        } else {
            sscanf(linha.c_str(), "%d %d", &origem, &destino);
        }
        nova_aresta(origem, destino, peso);
    }
    
    file.close();
}

void Grafo::imprimeGrafo() {
    cout << "INFORMAÇÕES DO GRAFO: " << nomeArquivo << endl;
    cout << "Grau: " << get_grau() << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Componentes conexas: " << n_conexo() << endl;
    cout << "Vertices Ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << "Arestas Ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
    cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;
    //cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    //cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    // cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << endl;
    // cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << std::endl;

    imprimeLista();
}

void Grafo::imprimeLista() {
  cerr << "Método imprimeLista chamado na classe base" << endl;
}

void Grafo::imprimeMatriz() {
  cerr << "Método imprimeMatriz chamado na classe base" << endl;
}