#include "GrafoMatriz.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

GrafoMatriz::GrafoMatriz(int n) : num_vertices(n) {
    matriz.resize(n, vector<int>(n, 0));
}

void GrafoMatriz::adicionar_aresta(int u, int v) {
    if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices) {
        cerr << "Erro: Índices fora do intervalo permitido." << endl;
        return;
    }
    matriz[u][v] = 1;
    matriz[v][u] = 1;
}

bool GrafoMatriz::eh_bipartido() {
    vector<int> cor(num_vertices, -1);
    for (int i = 0; i < num_vertices; i++) {
        if (cor[i] == -1) {
            if (!bfs_bipartido(i, cor)) {
                return false;
            }
        }
    }
    return true;
}

bool GrafoMatriz::bfs_bipartido(int src, vector<int> &cor) {
    queue<int> fila;
    fila.push(src);
    cor[src] = 0;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v = 0; v < num_vertices; v++) {
            if (matriz[u][v] == 1) {
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila.push(v);
                } else if (cor[v] == cor[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}