#include "grafo.h"
#include <fstream>  // Para manipulação de arquivos
#include <iostream> // Para entrada e saída
#include <string>   // Para manipulação de strings
#include <cstdlib>  // Para funções como atoi

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
    cerr << "Método novo_no chamado na classe base\n";
}

void Grafo::deleta_no(int id) {
    cerr << "Método deleta_no chamado na classe base\n";
}

void Grafo::nova_aresta(int origem, int destino, int peso) {
    cerr << "Método nova_aresta chamado na classe base\n";
}

void Grafo::deleta_aresta(int origem, int destino) {
    cerr << "Método deleta_aresta chamado na classe base\n";
}

void Grafo::carrega_grafo(const string& arquivo) {
    ifstream file(arquivo.c_str()); // Abrir o arquivo

    if (!file) {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
        exit(EXIT_FAILURE); // Encerra o programa em caso de erro
    }

    string linha;

    // Lê a primeira linha (configuração do grafo)
    if (getline(file, linha)) {
        int direcionado_int, verticePonderado_int, arestaPonderada_int;
        sscanf(linha.c_str(), "%d %d %d %d", &ordem, &direcionado_int, &verticePonderado_int, &arestaPonderada_int);
        direcionado = direcionado_int;
        verticePonderado = verticePonderado_int;
        arestaPonderada = arestaPonderada_int;
    }

    // Lê os pesos dos nós, se aplicável
    if (verticePonderado && getline(file, linha)) {
        int peso;
        for (int id = 1; id <= ordem; ++id) {
            size_t pos = linha.find(" ");
            if (pos != string::npos) {
                peso = atoi(linha.substr(0, pos).c_str());
                linha = linha.substr(pos + 1);
            } else {
                peso = atoi(linha.c_str());
            }
            novo_no(id, peso); // Adiciona o nó com o peso
        }
    }

    // Lê as arestas
    while (getline(file, linha)) {
        if (linha.empty()) continue; // Ignora linhas vazias

        int origem, destino, peso = 0;
        if (arestaPonderada) {
            sscanf(linha.c_str(), "%d %d %d", &origem, &destino, &peso);
        } else {
            sscanf(linha.c_str(), "%d %d", &origem, &destino);
        }
        nova_aresta(origem, destino, peso); // Adiciona a aresta
    }

    file.close(); // Fecha o arquivo    
}


void Grafo::imprimeGrafo() {
    cout << "INFORMAÇÕES DO GRAFO: " << nomeArquivo << endl;
    //cout << "Grau: " << get_grau() << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    //cout << "Componentes conexas: " << n_conexo() << endl;
    cout << "Vertices Ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << "Arestas Ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
    // cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;
    // cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << endl;
    // cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    // cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    // cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << std::endl;
}

/*
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
} */