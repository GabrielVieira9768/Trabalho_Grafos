#include "grafo_lista.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string> 

using namespace std;

GrafoLista::GrafoLista() : listaAdj(nullptr), pesosVertices(nullptr), grauVertices(nullptr) {}

GrafoLista::~GrafoLista() {
    if (listaAdj) {
        delete[] listaAdj; // Liberar o array alocado com new[]
    }

    if (pesosVertices) {
        delete[] pesosVertices; // Liberar o array alocado com new[]
    }

    if (grauVertices) {
        delete[] grauVertices; // Liberar o array alocado com new[]
    }
}

void GrafoLista::inicializaLista(int ordem) {
    this->ordem = ordem;

    // Alocar o array de ListaEncadeada com new[]
    listaAdj = new ListaEncadeada[ordem];

    // Alocar arrays para pesos e graus (se necessário)
    if (verticePonderado) {
        pesosVertices = new int[ordem](); // Inicializar com zero
    }

    grauVertices = new int[ordem](); // Inicializar com zero
}

void GrafoLista::adicionaAresta(int origem, int destino, int peso) {
    if(origem != destino){
        listaAdj[origem - 1].insereNo(destino, peso);
        grauVertices[origem - 1]++;
        grauVertices[destino - 1]++;

        if (!direcionado) {
            listaAdj[destino - 1].insereNo(origem, peso);
        }
    }
}


void GrafoLista::carrega_grafo(const string& arquivo) {
    nomeArquivo = arquivo;
    ifstream entrada(arquivo.c_str());
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string linha;

    // Lê a primeira linha com as configurações do grafo
    if (getline(entrada, linha)) {
        char* end;
        ordem = strtol(linha.c_str(), &end, 10);
        direcionado = (strtol(end, &end, 10) == 1);
        verticePonderado = (strtol(end, &end, 10) == 1);
        arestaPonderada = (strtol(end, &end, 10) == 1);
    }

    inicializaLista(ordem);

    // Lê os pesos dos vértices, se houver
    if (verticePonderado && getline(entrada, linha)) {
        char* token = strtok(const_cast<char*>(linha.c_str()), " ");
        for (int i = 0; i < ordem && token; i++) {
            pesosVertices[i] = atoi(token);
            token = strtok(nullptr, " ");
        }
    }

    // Lê as arestas do grafo
    while (getline(entrada, linha)) {
        char* end;
        int origem = strtol(linha.c_str(), &end, 10);
        int destino = strtol(end, &end, 10);
        int peso = arestaPonderada ? strtol(end, &end, 10) : 1;

        adicionaAresta(origem, destino, peso);
    }

    entrada.close();
}

bool GrafoLista::eh_completo() {
    int grauMaximo = this->ordem - 1; // O grau máximo de um vértice em um grafo completo

    for (int i = 0; i < this->ordem; ++i) {
        if (this->grauVertices[i] != grauMaximo) {
            return false;
        }
    }

    return true;
}


bool GrafoLista::eh_bipartido() {
    int n = this->ordem;
    int total = 1 << n; // Número total de divisões possíveis

    // Percorre todas as divisões possíveis dos vértices em dois conjuntos
    for (int mask = 0; mask < total; ++mask) {
        bool valido = true;

        // Verifica todas as arestas para ver se a divisão é válida
        for (int v = 0; v < n && valido; ++v) {
            No* no = listaAdj[v].getCabeca();
            while (no != nullptr && valido) {
                int destino = no->destino - 1; // Ajuste de índice

                // Se ambos os vértices estão no mesmo conjunto, a divisão não é válida
                if (((mask >> v) & 1) == ((mask >> destino) & 1)) {
                    valido = false;
                }
                no = no->prox;
            }
        }

        // Se encontramos uma divisão válida, o grafo é bipartido
        if (valido) return true;
    }

    // Se nenhuma divisão válida foi encontrada, o grafo não é bipartido
    return false;
}



int GrafoLista::n_conexo() {
    bool* visitado = new bool[ordem]();
    int n_componentes = 0;

    for (int i = 0; i < ordem; ++i) {
        if (!visitado[i]) {
            ++n_componentes;
            dfs(i, visitado);
        }
    }

    delete[] visitado;
    return n_componentes;
}

bool GrafoLista::eh_arvore() {
    bool* marcados = new bool[ordem];
    std::fill(marcados, marcados + ordem, false);  // Inicializa todos os elementos como 'false'

    // Verifica se o grafo é conexo (se existe apenas uma componente conexa)
    if (n_conexo() != 1) {
        delete[] marcados;
        return false;
    }

    bool existeCiclo = false;
    dfsDetectaCiclo(0, marcados, -1, existeCiclo);  // Inicia a busca por ciclos a partir do vértice 0

    delete[] marcados;  // Libera a memória alocada
    return !existeCiclo;  // Retorna verdadeiro se não houver ciclo
}



bool GrafoLista::possui_articulacao() {
    int* tempoDescoberta = new int[ordem]();
    int* low = new int[ordem]();
    int* pai = new int[ordem];
    bool* visitado = new bool[ordem]();
    bool temArticulacao = false;

    std::fill(pai, pai + ordem, -1);
    int tempo = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            dfsArticulacao(i, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);
        }
    }

    delete[] tempoDescoberta;
    delete[] low;
    delete[] pai;
    delete[] visitado;

    return temArticulacao;
}



bool GrafoLista::possui_ponte() {
    int* tempoDescoberta = new int[ordem]();
    int* low = new int[ordem]();
    int* pai = new int[ordem];
    bool* visitado = new bool[ordem]();
    bool temPonte = false;

    std::fill(pai, pai + ordem, -1);
    int tempo = 0;

    for (int i = 0; i < ordem; i++) {
        if (!visitado[i]) {
            dfsPonte(i, visitado, tempoDescoberta, low, pai, tempo, temPonte);
        }
    }

    delete[] tempoDescoberta;
    delete[] low;
    delete[] pai;
    delete[] visitado;

    return temPonte;
}


int GrafoLista::get_grau() {
    if (ordem == 0) {
        cerr << "O grafo está vazio." << endl;
        return -1; // Retorna -1 para indicar erro
    }

    int maiorGrau = grauVertices[0];

    for (int i = 0; i < ordem; i++) {
        if (grauVertices[i] > maiorGrau) {
            maiorGrau = grauVertices[i];
        }
    }

    return maiorGrau;
}

/*
3 // Grau
3 // Ordem
1 // Direcionado
2 // Componentes conexas
1 // Vertices ponderados
1 // Arestas ponderadas
0 // Completo
1 // Bipartido
0 // Arvore
1 // Aresta Ponte
1 // Vertice de Articulação
*/

void GrafoLista::novo_grafo(const string& arquivoEntrada, const string& arquivoSaida, int tentativas = 0) {
    const int MAX_TENTATIVAS = 5000;

    if (tentativas >= MAX_TENTATIVAS) {
        cerr << "Limite de tentativas atingido. Encerrando execução." << endl;
        return;
    }

    // Abrir o arquivo de entrada
    ifstream entrada(arquivoEntrada);
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return;
    }

    // Ler propriedades do arquivo de entrada
    int grau, ordem, componenteConexa;
    bool direcionado, verticePonderado, arestaPonderada, completo, bipartido, arvore, arestaPonte, verticeArticulacao;

    entrada >> grau >> ordem >> direcionado >> componenteConexa 
            >> verticePonderado >> arestaPonderada >> completo >> bipartido
            >> arvore >> arestaPonte >> verticeArticulacao;
    entrada.close();

    // Inicializar a lista de adjacência
    if (listaAdj) {
        delete[] listaAdj;
        listaAdj = nullptr;
    }
    inicializaLista(ordem);

    // Gerar pesos dos vértices aleatórios, se necessário
    int* pesosVertices = nullptr;

    if (verticePonderado) {
        pesosVertices = new int[ordem];
        for (int i = 0; i < ordem; ++i) {
            pesosVertices[i] = rand() % 100 + 1;
        }
    }

    // Gerar arestas aleatórias
    int numArestas = rand() % (ordem * (ordem - 1) / 2) + 1;
    for (int i = 0; i < numArestas; ++i) {
        int origem = rand() % ordem + 1;
        int destino = rand() % ordem + 1;
        int peso = arestaPonderada ? rand() % 100 + 1 : 1;

        if (origem != destino && !verificaArestaExistente(origem, destino)) {
            adicionaAresta(origem, destino, peso);
        }
    }

    // Verificar propriedades do grafo gerado
    bool condicoesAtendidas = true;
    
    condicoesAtendidas &= (completo == eh_completo());
    condicoesAtendidas &= (grau == get_grau());
    condicoesAtendidas &= (bipartido == eh_bipartido());
    condicoesAtendidas &= (verticeArticulacao == possui_articulacao());
    condicoesAtendidas &= (arvore == eh_arvore());
    condicoesAtendidas &= (arestaPonte == possui_ponte());
    condicoesAtendidas &= (componenteConexa == n_conexo());

    // Todas as condições satisfeitas
    ofstream saida(arquivoSaida, ios::trunc);
    if (!saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }

    // Salvar o grafo no arquivo de saída
    saida << ordem << " " << direcionado << " " << verticePonderado << " " << arestaPonderada << endl;

    if (verticePonderado) {
        for (int i = 0; i < ordem; ++i) {
            saida << pesosVertices[i] << (i == ordem - 1 ? "\n" : " ");
        }
    }

    for (int i = 0; i < ordem; ++i) {
        No* atual = listaAdj[i].getCabeca();
        while (atual) {
            saida << (i + 1) << " " << atual->destino << " " << atual->peso << endl;
            atual = atual->prox;
        }
    }
    saida.close();

    // Verificar se as condições foram atendidas
    if (condicoesAtendidas) {
        cout << "Grafo aleatório gerado e salvo em: " << arquivoSaida << endl;
    } else {
        condicoesAtendidas = false;
        novo_grafo(arquivoEntrada, arquivoSaida, tentativas + 1);
    }
}

bool GrafoLista::verificaArestaExistente(int origem, int destino) {
    No* atual = listaAdj[origem - 1].getCabeca();
    while (atual) {
        if (atual->destino == destino) {
            return true;
        }
        atual = atual->prox;
    }
    return false;
}


//////////////////////------AUX------/////////////////////

void GrafoLista::dfsPonte(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temPonte) {
    visitado[u] = true;
    tempoDescoberta[u] = low[u] = ++tempo;

    No* no = listaAdj[u].getCabeca();
    while (no != nullptr) {
        int v = no->destino - 1;

        if (!visitado[v]) {
            pai[v] = u;
            dfsPonte(v, visitado, tempoDescoberta, low, pai, tempo, temPonte);

            low[u] = std::min(low[u], low[v]);

            // Verifica se a aresta (u, v) é uma ponte
            if (low[v] > tempoDescoberta[u]) {
                temPonte = true;
            }
        } else if (v != pai[u]) {
            // Atualiza o low[u] considerando os vértices de retorno
            low[u] = std::min(low[u], tempoDescoberta[v]);
        }

        no = no->prox;
    }
}

void GrafoLista::dfsDetectaCiclo(int noAtual, bool marcados[], int pai, bool& existeCiclo) {
    if (existeCiclo) return;

    marcados[noAtual] = true;
    
    No* vizinho = listaAdj[noAtual].getCabeca();
    while (vizinho != nullptr) {
        int vizinhoDestino = vizinho->destino - 1;

        if (!marcados[vizinhoDestino]) {
            dfsDetectaCiclo(vizinhoDestino, marcados, noAtual, existeCiclo); 
        } else if (vizinhoDestino != pai) {
            // Encontrou um ciclo, então marca a variável
            existeCiclo = true;
            return;
        }
        vizinho = vizinho->prox;
    }
}

void GrafoLista::dfs(int vertice, bool visitado[]) {
    visitado[vertice] = true;
    
    No* no = listaAdj[vertice].getCabeca();
    while (no != nullptr) {
        int adj = no->destino - 1;
        if (!visitado[adj]) {
            dfs(adj, visitado);
        }
        no = no->prox;
    }
}

void GrafoLista::dfsArticulacao(int u, bool visitado[], int tempoDescoberta[], int low[], int pai[], int& tempo, bool& temArticulacao) {
    visitado[u] = true;
    tempoDescoberta[u] = low[u] = ++tempo;
    int filhos = 0;

    No* no = listaAdj[u].getCabeca();
    while (no != nullptr) {
        int v = no->destino - 1;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;
            dfsArticulacao(v, visitado, tempoDescoberta, low, pai, tempo, temArticulacao);

            low[u] = std::min(low[u], low[v]);

            // Verifica se a aresta (u, v) é uma articulação
            if ((pai[u] == -1 && filhos > 1) || (pai[u] != -1 && low[v] >= tempoDescoberta[u])) {
                temArticulacao = true;
            }
        } else if (v != pai[u]) {
            // Atualiza o low[u] considerando os vértices de retorno
            low[u] = std::min(low[u], tempoDescoberta[v]);
        }

        no = no->prox;
    }
}
