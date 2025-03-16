// Comando para compilar: g++ -o main.out main.cpp src/*.cpp -I./include/ -g -Wall -Werror
// Comando para rodar os arquivos: time|valgrind main.out -p -m|-l ./entradas/grafo2.txt
// Caso não dê para rodar sem o ./ no main.out é só executar a linha 'export PATH=$PATH:.' no terminal

#include <iostream>
#include <string>
#include "./grafo_lista.h"
#include "./grafo_matriz.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: main.out -p -m|-l <arquivo_entrada>" << endl;
        return 1;
    }

    string parametro = argv[1];
    string tipoRepresentacao = argv[2];
    string arquivoEntrada = argv[3];

    if (parametro == "-p") {
        if (tipoRepresentacao == "-m") {
            GrafoMatriz grafo;
            grafo.carrega_grafo(arquivoEntrada);
            //grafo.deleta_no(1);
            //grafo.deleta_primeira_aresta(2);
            grafo.imprimeGrafo();
        } else if (tipoRepresentacao == "-l") {
            GrafoLista grafo;
            grafo.carrega_grafo(arquivoEntrada);
            grafo.imprimeGrafo();
        } else {
            cerr << "Erro: Tipo de representação inválido. Use -m ou -l." << endl;
            return 1;
        }
    } else {
        cerr << "Erro: Comando inválido. Use -p." << endl;
        return 1;
    }

    return 0;
}