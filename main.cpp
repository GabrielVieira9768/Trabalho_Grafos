#include "grafo_lista.h"
#include "grafo_matriz.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Nome do arquivo que contém o grafo
    string arquivo = "grafo.txt";

    // Criando o grafo
    GrafoLista grafo;

    // Carregando o grafo do arquivo
    cout << "Carregando grafo do arquivo: " << arquivo << endl;
    grafo.carregaGrafo(arquivo);

    // Imprimindo o grafo carregado
    cout << "\nGrafo carregado com sucesso!" << endl;
    grafo.imprimeGrafo();

    if(grafo.eh_completo()){
        cout << "Eh Completo";
    }

    return 0;
}
