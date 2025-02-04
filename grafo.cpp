#include "grafo.h"
#include <iostream>

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

void novo_no(int id, int peso) {
    cerr << "Método novo_no chamado na classe base\n";
}

void deleta_no(int id) {
    cerr << "Método deleta_no chamado na classe base\n";
}

void nova_aresta(int origem, int destino, int peso) {
    cerr << "Método nova_aresta chamado na classe base\n";
}

void deleta_aresta(int origem, int destino) {
    cerr << "Método deleta_aresta chamado na classe base\n";
}

void Grafo::carrega_grafo(const string& arquivo) {
  
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
    cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << endl;
    cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << std::endl;
}