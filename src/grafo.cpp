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
    cout << "Grau: " << get_grau() << endl;
    cout << "Ordem: " << ordem << endl;
    cout << "Direcionado: " << (direcionado ? "Sim" : "Não") << endl;
    cout << "Componentes conexas: " << n_conexo() << endl;
    cout << "Vertices Ponderados: " << (verticePonderado ? "Sim" : "Não") << endl;
    cout << "Arestas Ponderadas: " << (arestaPonderada ? "Sim" : "Não") << endl;
    cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << endl;

    // calculaMenorDistancia();
    // imprimeLista();
    // imprimeMatriz();

    int terminais[] = {8, 12, 16, 24}; // Nó terminais do problema
    int tamanho = sizeof(terminais) / sizeof(terminais[0]);
    int numIteracoes = 100; // Número de iterações do GRASP
    float alpha = 0.3;      // Parâmetro alpha para construção da RCL (entre 0 e 1)

    cout << "Guloso Normal" << endl;
    steinerTree(terminais, tamanho, false);

    cout << endl;

    cout << "Guloso Randomizado" << endl;
    steinerTree(terminais, tamanho, true, 0.3);
}

void Grafo::imprimeLista()
{
    cerr << "Método imprimeLista chamado na classe base" << endl;
}

void Grafo::imprimeMatriz()
{
    cerr << "Método imprimeMatriz chamado na classe base" << endl;
}

void Grafo::steinerTree(int *terminais, int tamanho, bool randomizado, float alpha)
{
    if (tamanho == 0)
    {
        cerr << "Nenhum nó terminal foi fornecido." << endl;
        return;
    }

    // Arrays para armazenar predecessores e distâncias
    int *predecessor = new int[ordem + 1];
    float *distancia = new float[ordem + 1];

    // Array para marcar nós que fazem parte da árvore de Steiner
    bool *nosSteiner = new bool[ordem + 1](); // inicializa com zeros

    // Marcar os nós terminais como parte da árvore
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

    // Estrutura para a implementação manual do heap/fila de prioridade
    struct HeapNode
    {
        float distancia;
        int no;
    };

    // Heap simplificado - vetor + tamanho atual
    int maxHeapSize = ordem * ordem; // capacidade máxima estimada
    HeapNode *heap = new HeapNode[maxHeapSize];
    int heapSize = 0;

    // Funções auxiliares para o heap
    auto heapPush = [&](float dist, int node)
    {
        if (heapSize >= maxHeapSize)
            return;

        int i = heapSize++;
        heap[i].distancia = dist;
        heap[i].no = node;

        // Mover para cima (upheap)
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent].distancia <= heap[i].distancia)
                break;

            // Trocar com o pai
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

        // Mover para baixo (downheap)
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

    // Nova função para o guloso randomizado: escolhe um elemento aleatório entre os melhores
    auto heapRandomTop = [&]() -> HeapNode
    {
        if (heapSize <= 0)
            return heap[0]; // Retorna o primeiro elemento por segurança

        // Determina o limite para a lista restrita de candidatos
        float minDist = heap[0].distancia;
        float maxDist = minDist + alpha * (heap[heapSize - 1].distancia - minDist);
        
        // Contar quantos elementos estão dentro do limite
        int candidatosCount = 0;
        for (int i = 0; i < heapSize; i++)
        {
            if (heap[i].distancia <= maxDist)
                candidatosCount++;
            else
                break; // Como o heap está ordenado, podemos parar assim que encontrarmos um elemento fora do limite
        }
        
        if (candidatosCount <= 0)
            candidatosCount = 1; // Garantir pelo menos um candidato
        
        // Escolher aleatoriamente um dos candidatos
        int randomIndex = rand() % candidatosCount;
        return heap[randomIndex];
    };

    // Estrutura para arestas
    struct Aresta
    {
        int origem, destino;
    };

    // Array para armazenar as arestas da árvore
    Aresta *arestas = new Aresta[ordem * 2]; // no máximo ordem-1 arestas, mas para segurança
    int numArestas = 0;

    // Função para adicionar uma aresta se ela ainda não existe
    auto adicionarAresta = [&](int a, int b)
    {
        if (a > b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        // Verificar se a aresta já existe
        for (int i = 0; i < numArestas; i++)
        {
            if (arestas[i].origem == a && arestas[i].destino == b)
            {
                return;
            }
        }

        // Adicionar nova aresta
        arestas[numArestas].origem = a;
        arestas[numArestas].destino = b;
        numArestas++;
    };

    // Executa o Dijkstra para cada nó terminal
    for (int i = 0; i < tamanho; i++)
    {
        int t = terminais[i];

        // Reinicializa as estruturas para cada terminal
        for (int j = 0; j <= ordem; j++)
        {
            predecessor[j] = -1;
            distancia[j] = maximo;
        }

        distancia[t] = 0;
        heapSize = 0; // Reset do heap
        heapPush(0, t);

        // Algoritmo de Dijkstra, potencialmente randomizado
        while (!heapEmpty())
        {
            HeapNode atual;
            
            // Escolhe o próximo nó usando método guloso normal ou randomizado
            if (randomizado)
                atual = heapRandomTop();
            else
                atual = heapTop();
                
            int u = atual.no;
            float dist_u = atual.distancia;
            
            // Remove o nó escolhido do heap
            if (randomizado && atual.no != heap[0].no)
            {
                // Se escolhemos um nó que não está no topo, precisamos encontrá-lo e removê-lo
                for (int j = 0; j < heapSize; j++)
                {
                    if (heap[j].no == atual.no)
                    {
                        // Troca com o último elemento e diminui o tamanho
                        heap[j] = heap[heapSize - 1];
                        heapSize--;
                        
                        // Reorganiza o heap se necessário
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
                // Caso normal: remove o elemento do topo
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

        // Adicionar caminhos à árvore de Steiner
        for (int j = 0; j < tamanho; j++)
        {
            int destino = terminais[j];
            if (i != j)
            { // Não precisamos processar o mesmo terminal
                int atual = destino;
                while (predecessor[atual] != -1)
                {
                    int pai = predecessor[atual];

                    // Adicionar aresta
                    adicionarAresta(atual, pai);

                    // Marcar nós como parte da árvore
                    nosSteiner[atual] = true;
                    nosSteiner[pai] = true;

                    atual = pai;
                }
            }
        }
    }

    // Impressão dos nós da Árvore de Steiner
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

    // Impressão das arestas da Árvore de Steiner
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
        cout << endl;
    }

    // Libera a memória alocada
    delete[] predecessor;
    delete[] distancia;
    delete[] nosSteiner;
    delete[] heap;
    delete[] arestas;
}