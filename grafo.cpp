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
    // cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    // cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
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