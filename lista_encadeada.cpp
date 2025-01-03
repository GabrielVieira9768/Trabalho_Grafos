#include "lista_encadeada.h"
#include <iostream>
#include <cstdlib>

using namespace std;

ListaEncadeada::ListaEncadeada() : cabeca(nullptr) {}

ListaEncadeada::~ListaEncadeada() {
    No* atual = cabeca;
    while (atual) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

void ListaEncadeada::insereNo(int destino, int peso) {
    No* novoNo = new No(destino, peso);
    novoNo->prox = cabeca;
    cabeca = novoNo;
}

void ListaEncadeada::imprimeLista() {
    No* atual = cabeca;
    while (atual) {
        cout << "(" << atual->destino << ", " << atual->peso << ") -> ";
        atual = atual->prox;
    }
    cout << "NULL";
}

No* ListaEncadeada::getCabeca() const {
    return cabeca;
}
