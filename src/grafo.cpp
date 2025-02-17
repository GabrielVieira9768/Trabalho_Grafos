#include "./grafo.h"
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

void Grafo::novo_no(int id, float peso) {
    cerr << "Método novo_no chamado na classe base" << endl;
}

void Grafo::deleta_no(int id) {
    cerr << "Método deleta_no chamado na classe base" << endl;
}

void Grafo::nova_aresta(int origem, int destino, float peso) {
    cerr << "Método nova_aresta chamado na classe base"<< endl;
}

void Grafo::deleta_aresta(int origem, int destino) {
    cerr << "Método deleta_aresta chamado na classe base" << endl;
}

float Grafo::getPesoAresta(int origem, int destino) {
    return 0;
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

void Grafo::calculaMenorDistancia() {
    // Inicializa a matriz de distâncias com um valor alto (infinito)
    const float INF = 1e9f;  // Representa infinito para comparação
    float** dist = new float*[ordem];

    for (int i = 0; i < ordem; i++) {
        dist[i] = new float[ordem];
        for (int j = 0; j < ordem; j++) {
            if (i == j) {
                dist[i][j] = 0.0f;  // A distância de um nó para ele mesmo é 0
            } else if (existeAresta(i + 1, j + 1)) {
                dist[i][j] = getPesoAresta(i + 1, j + 1); // Assumindo que retorna float
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // Floyd-Warshall para encontrar menores distâncias
    for (int k = 0; k < ordem; k++) {
        for (int i = 0; i < ordem; i++) {
            for (int j = 0; j < ordem; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Pega maior menor caminho
    float cont = 0.0f;
    int inicio;
    int fim;
    
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            if (dist[i][j] < INF && dist[i][j] > cont) {
                cont = dist[i][j];
                inicio = i;
                fim = j;
            }
        }
    }

    cout << "Maior menor distância: (" << inicio + 1 << ", " << fim + 1 << ") - " << cont << endl;

    // Libera a memória alocada
    for (int i = 0; i < ordem; i++) {
        delete[] dist[i];
    }
    delete[] dist;
}


void Grafo::deleta_primeira_aresta(int id) {
    int* vizinhos = getVizinhos(id);
    int grau = getGrau(id);

    if (grau == 0) return;  // Não há arestas para deletar

    int menor = vizinhos[0];  // Inicializa com o primeiro vizinho

    for (int i = 1; i < grau; i++) {  // Começa do segundo vizinho
        if (vizinhos[i] < menor) {
            menor = vizinhos[i];
        }
    }

    cout << "Excluindo primeira aresta do nó " << id << "..." << endl;
    deleta_aresta(id, menor);
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
        float peso;
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
        
        int origem, destino;
        float peso = 0.0f;

        if (arestaPonderada) {
            sscanf(linha.c_str(), "%d %d %f", &origem, &destino, &peso);
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
    
    calculaMenorDistancia();
    imprimeLista();
    imprimeMatriz();
}

void Grafo::imprimeLista() {
  cerr << "Método imprimeLista chamado na classe base" << endl;
}

void Grafo::imprimeMatriz() {
  cerr << "Método imprimeMatriz chamado na classe base" << endl;
}