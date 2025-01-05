#include "grafo.h"
#include <iostream>

int Grafo::get_grau() {
    return this->grau;
}

int Grafo::get_ordem() {
    return this->ordem;
}

bool Grafo::eh_direcionado() {
    return this->direcionado;
}

bool Grafo::vertice_ponderado() {
    return this->verticePonderado;
}

void Grafo::carregaGrafo(const std::string& arquivo) {
    std::cout << "Erro: Método carregaGrafo chamado na classe base\n";
}

bool Grafo::aresta_ponderada() {
    return this->arestaPonderada;
}

bool Grafo::eh_completo() {
    return false;
}

bool Grafo::eh_bipartido() {
    return false;
}

bool Grafo::possui_ponte() {
    return false;
}

bool Grafo::possui_articulacao() {
    return false;
}

int Grafo::n_conexo() {
    return 0;
}

bool Grafo::eh_arvore() {
    return false;
}

void Grafo::imprimeGrafo() {
    cout << "INFORMAÇÕES DO GRAFO: " << nomeArquivo << endl;

    //cout << "Grau: " << grau << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Componentes conexas: " << n_conexo() << endl;
    cout << "Vertices Ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << "Arestas Ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
    cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;
    cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << endl;
    cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << endl;
    cout << "Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    //cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << endl;
    //cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << std::endl;
}