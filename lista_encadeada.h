#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

struct No {
    int destino;
    int peso;
    No* prox;

    No(int d, int p) : destino(d), peso(p), prox(nullptr) {}
};

class ListaEncadeada {
    private:
        No* cabeca;

    public:
        ListaEncadeada();
        ~ListaEncadeada();
        void insereNo(int destino, int peso);
        void imprimeLista();
        No* getCabeca() const;
};

#endif
