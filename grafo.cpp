#include "grafo.h"

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
    throw std::runtime_error("Método carregaGrafo chamado na classe base");
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