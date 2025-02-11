// Novo comando para executar o trabalho: g++ -std=c++11 -I./include -o main main.cpp ./src/grafo_lista.cpp ./src/lista_encadeada.cpp ./src/grafo.cpp
// Comando para rodar os arquivos: ./main -d -l ./entradas/nome_do_arquivo.txt

#include <iostream>
#include <string>
#include "./grafo_lista.h"
#include "./grafo_matriz.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: ./main -d -m|-l <./entradas/arquivo_entrada>" << endl;
        return 1;
    }

    string comando = argv[1];
    string tipoRepresentacao = argv[2];
    string arquivoEntrada = argv[3];
    int tentativas = 0;

    if (comando == "-d") {
        if (tipoRepresentacao == "-m") {
            // Criar o grafo usando as variáveis definidas
            GrafoMatriz grafo;
            grafo.carrega_grafo(arquivoEntrada);
            grafo.deleta_no(1);
            grafo.deleta_primeira_aresta(2);
            grafo.imprimeGrafo();
        } else if (tipoRepresentacao == "-l") {
            // Criar o grafo usando as variáveis definidas
            GrafoLista grafo;
            grafo.carrega_grafo(arquivoEntrada);
            grafo.deleta_no(1);
            grafo.deleta_primeira_aresta(2);
            grafo.imprimeGrafo();
        } else {
            cerr << "Erro: Tipo de representação inválido. Use -m ou -l." << endl;
            return 1;
        }
    } else {
        cerr << "Erro: Comando inválido. Use -d." << endl;
        return 1;
    }

    return 0;
}