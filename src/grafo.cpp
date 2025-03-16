#include "./grafo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define maximo 1000000

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
        {
            return false;
        }
    }

    return true;
}

int Grafo::n_conexo()
{
    bool *visitado = new bool[ordem + 1];
    for (int i = 1; i <= ordem; i++)
    {
        visitado[i] = false;
    }

    int contador = 0;

    for (int i = 1; i <= ordem; i++)
    {
        if (!visitado[i])
        {
            DFS(i, visitado);
            contador++;
        }
    }

    delete[] visitado;

    return contador;
}

void Grafo::DFS(int no, bool *visitado)
{
    visitado[no] = true;

    int *vizinhos = getVizinhos(no);

    if (vizinhos)
    {
        for (int i = 0; i < getGrau(no); i++)
        {
            int vizinho = vizinhos[i];
            if (!visitado[vizinho])
            {
                DFS(vizinho, visitado);
            }
        }

        delete[] vizinhos;
    }
}

void Grafo::calculaMenorDistancia()
{
    const float INF = 1e9f;
    float **dist = new float *[ordem];

    for (int i = 0; i < ordem; i++)
    {
        dist[i] = new float[ordem];
        for (int j = 0; j < ordem; j++)
        {
            if (i == j)
            {
                dist[i][j] = 0.0f;
            }
            else if (existeAresta(i + 1, j + 1))
            {
                dist[i][j] = getPesoAresta(i + 1, j + 1);
            }
            else
            {
                dist[i][j] = INF;
            }
        }
    }

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
        return;

    int menor = vizinhos[0];

    for (int i = 1; i < grau; i++)
    {
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

    if (getline(file, linha))
    {
        int direcionado_int, verticePonderado_int, arestaPonderada_int;
        sscanf(linha.c_str(), "%d %d %d %d", &ordem_int, &direcionado_int, &verticePonderado_int, &arestaPonderada_int);
        direcionado = direcionado_int;
        verticePonderado = verticePonderado_int;
        arestaPonderada = arestaPonderada_int;
    }

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

    int terminais[] = {8, 12, 16, 24};
    int tamanho = sizeof(terminais) / sizeof(terminais[0]);
    int numIteracoes = 100;
    float alpha = 0.3;

    cout << "Guloso Normal" << endl;
    steinerTree(terminais, tamanho, false);

    cout << endl;

    cout << "Guloso Randomizado" << endl;
    steinerTree(terminais, tamanho, true, 0.3);

    cout << "Guloso Randomizado Reativo" << endl;
    steinerTree(terminais, tamanho, true, 0.3, true);
}

void Grafo::imprimeLista()
{
    cerr << "Método imprimeLista chamado na classe base" << endl;
}

void Grafo::imprimeMatriz()
{
    cerr << "Método imprimeMatriz chamado na classe base" << endl;
}

struct Aresta
{
    int origem, destino;
};


void Grafo::steinerTree(int *terminais, int tamanho, bool randomizado, float alpha, bool reativo)
{
    if (tamanho == 0)
    {
        cerr << "Nenhum nó terminal foi fornecido." << endl;
        return;
    }

    const int numAlphas = 5;
    float alphas[numAlphas] = {0.1, 0.2, 0.3, 0.4, 0.5};
    float probabilidades[numAlphas] = {0.2, 0.2, 0.2, 0.2, 0.2};
    int contagem[numAlphas] = {0};
    float mediaCustos[numAlphas] = {0.0};

    float melhorCusto = maximo;
    bool *melhorSolucaoNos = new bool[ordem + 1]();
    int melhorNumArestas = 0;
    int *melhorArestasOrigem = new int[ordem * 2];
    int *melhorArestasDestino = new int[ordem * 2];

    int numIteracoes = 100;

    for (int iter = 0; iter < (reativo ? numIteracoes : 1); iter++)
    {
        float alphaAtual = alpha;

        if (reativo && randomizado)
        {
            float r = static_cast<float>(rand()) / RAND_MAX;
            float soma = 0.0;
            int escolhido = 0;
            for (int i = 0; i < numAlphas; i++)
            {
                soma += probabilidades[i];
                if (r <= soma)
                {
                    escolhido = i;
                    break;
                }
            }

            alphaAtual = alphas[escolhido];
            contagem[escolhido]++;
        }

        int *predecessor = new int[ordem + 1];
        float *distancia = new float[ordem + 1];

        bool *nosSteiner = new bool[ordem + 1]();

        for (int i = 0; i < tamanho; i++)
        {
            int t = terminais[i];
            if (t >= 1 && t <= ordem)
            {
                nosSteiner[t] = true;
            }
            else
            {
                cerr << "Erro: nó terminal fora do intervalo válido." << endl;
                delete[] predecessor;
                delete[] distancia;
                delete[] nosSteiner;
                return;
            }
        }

        struct HeapNode
        {
            float distancia;
            int no;
        };

        int maxHeapSize = ordem * ordem;
        HeapNode *heap = new HeapNode[maxHeapSize];
        int heapSize = 0;

        auto heapPush = [&](float dist, int node)
        {
            if (heapSize >= maxHeapSize)
                return;

            int i = heapSize++;
            heap[i].distancia = dist;
            heap[i].no = node;

            while (i > 0)
            {
                int parent = (i - 1) / 2;
                if (heap[parent].distancia <= heap[i].distancia)
                    break;

                HeapNode temp = heap[i];
                heap[i] = heap[parent];
                heap[parent] = temp;

                i = parent;
            }
        };

        auto heapPop = [&]()
        {
            if (heapSize <= 0)
                return;

            heap[0] = heap[--heapSize];

            int i = 0;
            while (true)
            {
                int smallest = i;
                int left = 2 * i + 1;
                int right = 2 * i + 2;

                if (left < heapSize && heap[left].distancia < heap[smallest].distancia)
                    smallest = left;

                if (right < heapSize && heap[right].distancia < heap[smallest].distancia)
                    smallest = right;

                if (smallest == i)
                    break;

                // Trocar com o menor filho
                HeapNode temp = heap[i];
                heap[i] = heap[smallest];
                heap[smallest] = temp;

                i = smallest;
            }
        };

        auto heapTop = [&]() -> HeapNode
        {
            return heap[0];
        };

        auto heapEmpty = [&]() -> bool
        {
            return heapSize == 0;
        };

        auto heapRandomTop = [&]() -> HeapNode
        {
            if (heapSize <= 0)
                return heap[0];

            float minDist = heap[0].distancia;
            float maxDist = minDist + alphaAtual * (heap[heapSize - 1].distancia - minDist);

            int candidatosCount = 0;
            for (int i = 0; i < heapSize; i++)
            {
                if (heap[i].distancia <= maxDist)
                    candidatosCount++;
                else
                    break;
            }

            if (candidatosCount <= 0)
                candidatosCount = 1;

            int randomIndex = rand() % candidatosCount;
            return heap[randomIndex];
        };

        struct Aresta
        {
            int origem, destino;
        };

        Aresta *arestas = new Aresta[ordem * 2];
        int numArestas = 0;

        auto adicionarAresta = [&](int a, int b)
        {
            if (a > b)
            {
                int temp = a;
                a = b;
                b = temp;
            }

            for (int i = 0; i < numArestas; i++)
            {
                if (arestas[i].origem == a && arestas[i].destino == b)
                {
                    return;
                }
            }

            arestas[numArestas].origem = a;
            arestas[numArestas].destino = b;
            numArestas++;
        };

        for (int i = 0; i < tamanho; i++)
        {
            int t = terminais[i];

            for (int j = 0; j <= ordem; j++)
            {
                predecessor[j] = -1;
                distancia[j] = maximo;
            }

            distancia[t] = 0;
            heapSize = 0;
            heapPush(0, t);

            while (!heapEmpty())
            {
                HeapNode atual;

                if (randomizado)
                    atual = heapRandomTop();
                else
                    atual = heapTop();

                int u = atual.no;
                float dist_u = atual.distancia;

                if (randomizado && atual.no != heap[0].no)
                {
                    for (int j = 0; j < heapSize; j++)
                    {
                        if (heap[j].no == atual.no)
                        {
                            heap[j] = heap[heapSize - 1];
                            heapSize--;

                            while (j > 0)
                            {
                                int parent = (j - 1) / 2;
                                if (heap[parent].distancia <= heap[j].distancia)
                                    break;

                                HeapNode temp = heap[j];
                                heap[j] = heap[parent];
                                heap[parent] = temp;

                                j = parent;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    heapPop();
                }

                if (dist_u > distancia[u])
                    continue;

                int *vizinhos = getVizinhos(u);
                int grau = getGrau(u);

                if (!vizinhos)
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
                        heapPush(distancia[v], v);
                    }
                }

                delete[] vizinhos;
            }

            for (int j = 0; j < tamanho; j++)
            {
                int destino = terminais[j];
                if (i != j)
                {
                    int atual = destino;
                    while (predecessor[atual] != -1)
                    {
                        int pai = predecessor[atual];

                        adicionarAresta(atual, pai);

                        nosSteiner[atual] = true;
                        nosSteiner[pai] = true;

                        atual = pai;
                    }
                }
            }
        }

        float custo = 0.0;
        for (int i = 0; i < numArestas; i++)
        {
            custo += getPesoAresta(arestas[i].origem, arestas[i].destino);
        }

        if (reativo && custo < melhorCusto)
        {
            melhorCusto = custo;
            for (int i = 1; i <= ordem; i++)
            {
                melhorSolucaoNos[i] = nosSteiner[i];
            }
            melhorNumArestas = numArestas;
            for (int i = 0; i < numArestas; i++)
            {
                melhorArestasOrigem[i] = arestas[i].origem;
                melhorArestasDestino[i] = arestas[i].destino;
            }
        }

        if (reativo && randomizado)
        {
            float somaInversa = 0.0;
            for (int i = 0; i < numAlphas; i++)
            {
                if (contagem[i] > 0)
                {
                    somaInversa += 1.0 / mediaCustos[i];
                }
            }

            for (int i = 0; i < numAlphas; i++)
            {
                if (contagem[i] > 0)
                {
                    probabilidades[i] = (1.0 / mediaCustos[i]) / somaInversa;
                }
            }
        }

        if (!reativo)
        {
            cout << "Árvore de Steiner " << (randomizado ? "randomizada" : "normal") << " encontrada com os nós: ";
            int contNos = 0;
            for (int i = 1; i <= ordem; i++)
            {
                if (nosSteiner[i])
                {
                    cout << i << " ";
                    contNos++;
                }
            }
            cout << endl;

            cout << "E com as arestas: ";
            if (numArestas == 0)
            {
                cout << "Nenhuma aresta encontrada." << endl;
            }
            else
            {
                for (int i = 0; i < numArestas; i++)
                {
                    cout << "(" << arestas[i].origem << ", " << arestas[i].destino << ") ";
                }
                cout << endl << endl;
            }
        }

        delete[] predecessor;
        delete[] distancia;
        delete[] nosSteiner;
        delete[] heap;
        delete[] arestas;
    }

    if (reativo)
    {
        cout << "Melhor custo encontrado: " << melhorCusto << endl;
        cout << "Melhor solução com os nós: ";
        for (int i = 1; i <= ordem; i++)
        {
            if (melhorSolucaoNos[i])
            {
                cout << i << " ";
            }
        }
        cout << endl;

        cout << "E com as arestas: ";
        for (int i = 0; i < melhorNumArestas; i++)
        {
            cout << "(" << melhorArestasOrigem[i] << ", " << melhorArestasDestino[i] << ") ";
        }
        cout << endl;
    }

    delete[] melhorSolucaoNos;
    delete[] melhorArestasOrigem;
    delete[] melhorArestasDestino;
}