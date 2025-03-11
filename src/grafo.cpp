#include "./grafo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define maximo 1000000;

using namespace std;

int Grafo::get_ordem()
{
    return this->ordem;
}

bool Grafo::eh_direcionado()
{
    return this->direcionado;
}

bool Grafo::vertice_ponderado()
{
    return this->verticePonderado;
}

bool Grafo::aresta_ponderada()
{
    return this->arestaPonderada;
}

void Grafo::novo_no(int id, float peso)
{
    cerr << "Método novo_no chamado na classe base" << endl;
}

void Grafo::deleta_no(int id)
{
    cerr << "Método deleta_no chamado na classe base" << endl;
}

void Grafo::nova_aresta(int origem, int destino, float peso)
{
    cerr << "Método nova_aresta chamado na classe base" << endl;
}

void Grafo::deleta_aresta(int origem, int destino)
{
    cerr << "Método deleta_aresta chamado na classe base" << endl;
}

float Grafo::getPesoAresta(int origem, int destino)
{
    return 0;
}

bool Grafo::existeNo(int id)
{
    return false;
}

bool Grafo::existeAresta(int origem, int destino)
{
    return false;
}

int *Grafo::getVizinhos(int id)
{
    return 0;
}

int Grafo::getGrau(int id)
{
    return 0;
}

int Grafo::getNumArestas()
{
    return 0;
}

int Grafo::get_grau()
{
    int maiorGrau = 0;

    for (int i = 1; i <= ordem; i++)
    {
        if (getGrau(i) > maiorGrau)
        {
            maiorGrau = getGrau(i);
        }
    }

    return maiorGrau;
}

bool Grafo::eh_completo()
{
    for (int i = 1; i <= ordem; i++)
    {
        if (getGrau(i) != ordem - 1)
        { // Verifica se cada nó tem grau igual (ordem - 1)
            return false;
        }
    }

    return true;
}

int Grafo::n_conexo()
{
    // Aloca um array para marcar os nós visitados
    bool *visitado = new bool[ordem + 1]; // +1 porque os nós começam de 1
    for (int i = 1; i <= ordem; i++)
    {
        visitado[i] = false;
    }

    int contador = 0;

    // Percorre todos os nós do grafo
    for (int i = 1; i <= ordem; i++)
    {
        if (!visitado[i])
        {
            // Se o nó não foi visitado, inicia uma DFS a partir dele
            DFS(i, visitado);
            contador++; // Incrementa o contador de componentes conexos
        }
    }

    // Libera a memória alocada para o array de visitados
    delete[] visitado;

    return contador;
}

void Grafo::DFS(int no, bool *visitado)
{
    // Marca o nó como visitado
    visitado[no] = true;

    // Obtém os vizinhos do nó
    int *vizinhos = getVizinhos(no);

    // Se o nó tiver vizinhos, percorre cada um deles
    if (vizinhos)
    {
        for (int i = 0; i < getGrau(no); i++)
        {
            int vizinho = vizinhos[i];
            if (!visitado[vizinho])
            {
                // Se o vizinho não foi visitado, realiza uma DFS a partir dele
                DFS(vizinho, visitado);
            }
        }

        // Libera a memória alocada para o array de vizinhos
        delete[] vizinhos;
    }
}

void Grafo::calculaMenorDistancia()
{
    // Inicializa a matriz de distâncias com um valor alto (infinito)
    const float INF = 1e9f; // Representa infinito para comparação
    float **dist = new float *[ordem];

    for (int i = 0; i < ordem; i++)
    {
        dist[i] = new float[ordem];
        for (int j = 0; j < ordem; j++)
        {
            if (i == j)
            {
                dist[i][j] = 0.0f; // A distância de um nó para ele mesmo é 0
            }
            else if (existeAresta(i + 1, j + 1))
            {
                dist[i][j] = getPesoAresta(i + 1, j + 1); // Assumindo que retorna float
            }
            else
            {
                dist[i][j] = INF;
            }
        }
    }

    // Floyd-Warshall para encontrar menores distâncias
    for (int k = 0; k < ordem; k++)
    {
        for (int i = 0; i < ordem; i++)
        {
            for (int j = 0; j < ordem; j++)
            {
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Pega maior menor caminho
    float cont = 0.0f;
    int inicio;
    int fim;

    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (dist[i][j] < INF && dist[i][j] > cont)
            {
                cont = dist[i][j];
                inicio = i;
                fim = j;
            }
        }
    }

    cout << "Maior menor distância: (" << inicio + 1 << ", " << fim + 1 << ") - " << cont << endl;

    // Libera a memória alocada
    for (int i = 0; i < ordem; i++)
    {
        delete[] dist[i];
    }
    delete[] dist;
}

void Grafo::deleta_primeira_aresta(int id)
{
    int *vizinhos = getVizinhos(id);
    int grau = getGrau(id);

    if (grau == 0)
        return; // Não há arestas para deletar

    int menor = vizinhos[0]; // Inicializa com o primeiro vizinho

    for (int i = 1; i < grau; i++)
    { // Começa do segundo vizinho
        if (vizinhos[i] < menor)
        {
            menor = vizinhos[i];
        }
    }

    cout << "Excluindo primeira aresta do nó " << id << "..." << endl;
    deleta_aresta(id, menor);
}

void Grafo::carrega_grafo(const string &arquivo)
{
    ifstream file(arquivo.c_str());

    if (!file)
    {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
        exit(EXIT_FAILURE);
    }

    string linha;
    int ordem_int;

    // Lê a descrição do grafo
    if (getline(file, linha))
    {
        int direcionado_int, verticePonderado_int, arestaPonderada_int;
        sscanf(linha.c_str(), "%d %d %d %d", &ordem_int, &direcionado_int, &verticePonderado_int, &arestaPonderada_int);
        direcionado = direcionado_int;
        verticePonderado = verticePonderado_int;
        arestaPonderada = arestaPonderada_int;
    }

    // Lê os pesos dos nós se ponderado
    if (verticePonderado && getline(file, linha))
    {
        float peso;
        for (int id = 1; id <= ordem_int; ++id)
        {
            size_t pos = linha.find(" ");
            if (pos != string::npos)
            {
                peso = atoi(linha.substr(0, pos).c_str());
                linha = linha.substr(pos + 1);
            }
            else
            {
                peso = atoi(linha.c_str());
            }
            novo_no(id, peso);
        }
    }

    // Lê as arestas
    while (getline(file, linha))
    {
        if (linha.empty())
            continue;

        int origem, destino;
        float peso = 0.0f;

        if (arestaPonderada)
        {
            sscanf(linha.c_str(), "%d %d %f", &origem, &destino, &peso);
        }
        else
        {
            sscanf(linha.c_str(), "%d %d", &origem, &destino);
        }
        nova_aresta(origem, destino, peso);
    }

    file.close();
}

void Grafo::imprimeGrafo()
{
    cout << "INFORMAÇÕES DO GRAFO: " << nomeArquivo << endl;
    // cout << "Grau: " << get_grau() << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    // cout << "Componentes conexas: " << n_conexo() << endl;
    // cout << "Vertices Ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    // cout << "Arestas Ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
    // cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;

    // calculaMenorDistancia();
    // imprimeLista();
    // imprimeMatriz();

    int terminais[] = {1, 3, 4, 5}; // Nó terminais do problema
    int tamanho = sizeof(terminais) / sizeof(terminais[0]);
    cout << "Guloso Normal" << endl;
    steinerTree(terminais, tamanho, false);

    cout << endl;

    cout << "Guloso Randomizado" << endl;
    steinerTree(terminais, tamanho, true, 0.5);
}

void Grafo::imprimeLista()
{
    cerr << "Método imprimeLista chamado na classe base" << endl;
}

void Grafo::imprimeMatriz()
{
    cerr << "Método imprimeMatriz chamado na classe base" << endl;
}

// Implementação do método de Steiner
const int MAX_NOS = 6000; // Defina um tamanho máximo para os nós

struct Pair
{
    float primeiro;
    int segundo;
};

void trocar(Pair &a, Pair &b)
{
    Pair temp = a;
    a = b;
    b = temp;
}

void agrupar(Pair arr[], int n, int i)
{
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && arr[esq].primeiro > arr[maior].primeiro)
        maior = esq;

    if (dir < n && arr[dir].primeiro > arr[maior].primeiro)
        maior = dir;

    if (maior != i)
    {
        trocar(arr[i], arr[maior]);
        agrupar(arr, n, maior);
    }
}

void push(Pair arr[], int &n, Pair valor)
{
    arr[n++] = valor;
    for (int i = n / 2 - 1; i >= 0; i--)
        agrupar(arr, n, i);
}

Pair pop(Pair arr[], int &n)
{
    Pair root = arr[0];
    arr[0] = arr[--n];
    agrupar(arr, n, 0);
    return root;
}

Pair popRandomizado(Pair arr[], int &n, float alpha)
{
    // Determinar o número de melhores nós a considerar
    int k = max(1, (int)(alpha * n));

    // Selecionar aleatoriamente entre os k melhores nós
    int idx = rand() % k;
    Pair selecionado = arr[idx];

    // Remover o nó selecionado da heap
    arr[idx] = arr[--n];
    agrupar(arr, n, idx);

    return selecionado;
}

void Grafo::steinerTree(int *terminais, int tamanho, bool randomizado, float alpha)
{
    // Início da medição de tempo
    clock_t inicio = clock();

    if (tamanho == 0)
    {
        cerr << "Nenhum nó terminal foi fornecido." << endl;
        return;
    }

    int conjuntoSteiner[MAX_NOS] = {0};
    int conjuntoSteinerSize = 0;
    for (int i = 0; i < tamanho; i++)
    {
        conjuntoSteiner[conjuntoSteinerSize++] = terminais[i];
    }

    int predecessor[MAX_NOS];
    float distancia[MAX_NOS];

    for (int i = 0; i < MAX_NOS; i++)
    {
        predecessor[i] = -1;
        distancia[i] = maximo;
    }

    Pair pq[MAX_NOS];
    int pqSize = 0;

    // Executar Dijkstra para cada terminal
    for (int i = 0; i < tamanho; i++)
    {
        int t = terminais[i];
        if (t < 1 || t > ordem)
        {
            cerr << "Erro: nó terminal fora do intervalo válido." << endl;
            return;
        }
        distancia[t] = 0;
        push(pq, pqSize, {0, t});

        while (pqSize > 0)
        {
            Pair top;
            if (randomizado)
            {
                top = popRandomizado(pq, pqSize, alpha);
            }
            else
            {
                top = pop(pq, pqSize);
            }
            int u = top.segundo;
            float dist_u = top.primeiro;

            if (dist_u > distancia[u])
                continue;

            int *vizinhos = getVizinhos(u);
            int grau = getGrau(u);
            if (vizinhos == nullptr)
                continue;

            for (int j = 0; j < grau; j++)
            {
                int v = vizinhos[j];
                if (v < 1 || v > ordem)
                    continue;

                float peso = getPesoAresta(u, v);
                if (distancia[v] > dist_u + peso)
                {
                    distancia[v] = dist_u + peso;
                    predecessor[v] = u;
                    push(pq, pqSize, {distancia[v], v});
                }
            }
            delete[] vizinhos;
        }
    }

    // Construir a árvore de Steiner
    int arestasSteiner[MAX_NOS][2];
    int arestasSteinerSize = 0;
    bool visitado[MAX_NOS] = {false};
    float pesoTotal = 0.0;

    for (int i = 0; i < tamanho; i++)
    {
        int atual = terminais[i];
        while (predecessor[atual] != -1 && !visitado[atual])
        {
            visitado[atual] = true;
            int pai = predecessor[atual];

            // Adiciona a aresta se ainda não foi inserida
            bool existe = false;
            for (int j = 0; j < arestasSteinerSize; j++)
            {
                if ((arestasSteiner[j][0] == min(atual, pai) && arestasSteiner[j][1] == max(atual, pai)))
                {
                    existe = true;
                    break;
                }
            }
            if (!existe)
            {
                arestasSteiner[arestasSteinerSize][0] = min(atual, pai);
                arestasSteiner[arestasSteinerSize][1] = max(atual, pai);
                pesoTotal += getPesoAresta(atual, pai); // Soma o peso da aresta
                arestasSteinerSize++;
            }

            // Adiciona os nós no conjunto Steiner
            bool noExiste = false;
            for (int j = 0; j < conjuntoSteinerSize; j++)
            {
                if (conjuntoSteiner[j] == atual)
                {
                    noExiste = true;
                    break;
                }
            }
            if (!noExiste)
            {
                conjuntoSteiner[conjuntoSteinerSize++] = atual;
            }

            noExiste = false;
            for (int j = 0; j < conjuntoSteinerSize; j++)
            {
                if (conjuntoSteiner[j] == pai)
                {
                    noExiste = true;
                    break;
                }
            }
            if (!noExiste)
            {
                conjuntoSteiner[conjuntoSteinerSize++] = pai;
            }

            atual = pai;
        }
    }

    // Impressão única da resposta final
    cout << "Árvore de Steiner encontrada com os nós: ";
    for (int i = 0; i < conjuntoSteinerSize; i++)
    {
        cout << conjuntoSteiner[i] << " ";
    }
    cout << endl;

    cout << "E com as arestas: ";
    if (arestasSteinerSize == 0)
    {
        cout << "Nenhuma aresta encontrada." << endl;
    }
    else
    {
        for (int i = 0; i < arestasSteinerSize; i++)
        {
            cout << "(" << arestasSteiner[i][0] << ", " << arestasSteiner[i][1] << ") ";
        }
        cout << endl;
    }

    // Impressão do somatório do peso
    cout << "Peso total da Árvore de Steiner: " << pesoTotal << endl;

    // Fim da medição de tempo
    clock_t fim = clock();
    double tempo_execucao = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << fixed << setprecision(6); // Numero de casa decimais
    cout << "Tempo de execução: " << tempo_execucao << " segundos" << endl;
}
;

// void Grafo::steinerTree(int *terminais, int tamanho) {
//     // Início da medição de tempo
//     clock_t inicio = clock();

//     if (tamanho == 0) {
//         cerr << "Nenhum nó terminal foi fornecido." << endl;
//         return;
//     }

//     int conjuntoSteiner[MAX_NOS] = {0};
//     int conjuntoSteinerSize = 0;
//     for (int i = 0; i < tamanho; i++) {
//         conjuntoSteiner[conjuntoSteinerSize++] = terminais[i];
//     }

//     int predecessor[MAX_NOS];
//     float distancia[MAX_NOS];

//     for (int i = 0; i < MAX_NOS; i++) {
//         predecessor[i] = -1;
//         distancia[i] = maximo;
//     }

//     Pair pq[MAX_NOS];
//     int pqSize = 0;

//     // Executar Dijkstra para cada terminal
//     for (int i = 0; i < tamanho; i++) {
//         int t = terminais[i];
//         if (t < 1 || t > ordem) {
//             cerr << "Erro: nó terminal fora do intervalo válido." << endl;
//             return;
//         }
//         distancia[t] = 0;
//         push(pq, pqSize, {0, t});

//         while (pqSize > 0) {
//             Pair top = pop(pq, pqSize);
//             int u = top.segundo;
//             float dist_u = top.primeiro;

//             if (dist_u > distancia[u])
//                 continue;

//             int *vizinhos = getVizinhos(u);
//             int grau = getGrau(u);
//             if (vizinhos == nullptr)
//                 continue;

//             for (int j = 0; j < grau; j++) {
//                 int v = vizinhos[j];
//                 if (v < 1 || v > ordem)
//                     continue;

//                 float peso = getPesoAresta(u, v);
//                 if (distancia[v] > dist_u + peso) {
//                     distancia[v] = dist_u + peso;
//                     predecessor[v] = u;
//                     push(pq, pqSize, {distancia[v], v});
//                 }
//             }
//             delete[] vizinhos;
//         }
//     }

//     // Construir a árvore de Steiner
//     int arestasSteiner[MAX_NOS][2];
//     int arestasSteinerSize = 0;
//     bool visitado[MAX_NOS] = {false};
//     float pesoTotal = 0.0;

//     for (int i = 0; i < tamanho; i++) {
//         int atual = terminais[i];
//         while (predecessor[atual] != -1 && !visitado[atual]) {
//             visitado[atual] = true;
//             int pai = predecessor[atual];

//             // Adiciona a aresta se ainda não foi inserida
//             bool existe = false;
//             for (int j = 0; j < arestasSteinerSize; j++) {
//                 if ((arestasSteiner[j][0] == min(atual, pai) && arestasSteiner[j][1] == max(atual, pai))) {
//                     existe = true;
//                     break;
//                 }
//             }
//             if (!existe) {
//                 arestasSteiner[arestasSteinerSize][0] = min(atual, pai);
//                 arestasSteiner[arestasSteinerSize][1] = max(atual, pai);
//                 pesoTotal += getPesoAresta(atual, pai); // Soma o peso da aresta
//                 arestasSteinerSize++;
//             }

//             // Adiciona os nós no conjunto Steiner
//             bool noExiste = false;
//             for (int j = 0; j < conjuntoSteinerSize; j++) {
//                 if (conjuntoSteiner[j] == atual) {
//                     noExiste = true;
//                     break;
//                 }
//             }
//             if (!noExiste) {
//                 conjuntoSteiner[conjuntoSteinerSize++] = atual;
//             }

//             noExiste = false;
//             for (int j = 0; j < conjuntoSteinerSize; j++) {
//                 if (conjuntoSteiner[j] == pai) {
//                     noExiste = true;
//                     break;
//                 }
//             }
//             if (!noExiste) {
//                 conjuntoSteiner[conjuntoSteinerSize++] = pai;
//             }

//             atual = pai;
//         }
//     }

//     // Depuração extra: Exibir predecessores
//     /*
//     cout << "Predecessores:" << endl;
//     for (int i = 1; i <= ordem; i++) {
//         if (predecessor[i] != -1) {
//             cout << "Nó " << i << " -> Predecessor: " << predecessor[i] << endl;
//         }
//     }
//     */

//     // Impressão única da resposta final
//     cout << "Árvore de Steiner encontrada com os nós: ";
//     for (int i = 0; i < conjuntoSteinerSize; i++) {
//         cout << conjuntoSteiner[i] << " ";
//     }
//     cout << endl;

//     cout << "E com as arestas: ";
//     if (arestasSteinerSize == 0) {
//         cout << "Nenhuma aresta encontrada." << endl;
//     } else {
//         for (int i = 0; i < arestasSteinerSize; i++) {
//             cout << "(" << arestasSteiner[i][0] << ", " << arestasSteiner[i][1] << ") ";
//         }
//         cout << endl;
//     }

//     // Impressão do somatório do peso
//     cout << "Peso total da Árvore de Steiner: " << pesoTotal << endl;

//     // Fim da medição de tempo
//     clock_t fim = clock();
//     double tempo_execucao = double(fim - inicio) / CLOCKS_PER_SEC;
//     cout << fixed << setprecision(6); // Numero de casa decimais
//     cout << "Tempo de execução: " << tempo_execucao << " segundos" << endl;
// }.