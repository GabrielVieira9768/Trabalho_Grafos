#include "GrafoMatriz.h"
#include <iostream>

GrafoMatriz::GrafoMatriz(int n) : num_vertices(n) {
    matriz.resize(n, std::vector<int>(n, 0));
}

void GrafoMatriz::adicionar_aresta(int u, int v) {
    matriz[u][v] = 1;
    matriz[v][u] = 1;
}

bool GrafoMatriz::eh_bipartido() {
    std::vector<int> cor(numero_vertices, -1);
    for (int i = 0; i < numero_vertices; i++) {
        if (cor[i] == -1) {
            if (!bfs_bipartido(i, cor)) {
                return false;
            }
        }
    }
    return true;
}

bool GrafoMatriz::bfs_bipartido(int src, std::vector<int> &cor) {
    std::queue<int> fila;
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
