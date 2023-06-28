/*

Estruturas de Dados Avançadas (EDA) – INF1010
Departamento de Informática – PUC-Rio
2023.1
Tarefa 5 – Algoritmos sobre Grafos
Dado o grafo:
1) Represente o grafo acima usando lista de adjacências.
2) Implemente na Linguagem C os seguintes algoritmos, criando o TDA de grafos:
a) Calcule o caminho mais curto para os nós, a partir do vértice A, utilizando o algoritmo
de Dijkstra.
b) Indicar um caminho de uma busca em profundidade, a partir do vértice A.
Orientações de entrega:
Faça o upload no site do EAD dos seguintes:
 TDA de grafos contendo os arquivos .c e .h correspondentes
 Relatório em .pdf contendo:
• Identificação. Nome e matricula do(s) aluno(s), sendo no máximo 2 alunos por
trabalho;
• Introdução. Breve descrição sobre o conteúdo do trabalho;
• Estrutura do programa. Descrição da interface e as funções implementadas;
• Solução. Descrição da solução de cada algoritmo, incluindo capturas do código
fonte e a saída do programa;
• Observações e conclusões. Descrição de aspectos que precisem ser destacados,
tais como dificuldades e facilidades encontradas.
Data de Entrega: Até 23:59 do dia 28/junho/2023
Atenção:
 Trabalhos entregues com atraso sofrerão perda de 10% de sua nota por cada dia após
o prazo de entrega.

*/

#include <stdio.h>
#include <stdlib.h>

#include "set.h"

#define SIZEQUEUE 100
#define INFINITY 100000000

struct no
{
    int vtx;
    int dist;
    struct no *next;
};
struct no *criano(int);

struct Graph
{
    int qtd_vtx;
    struct no **adjLists;
};

struct priorityqueue
{
    int qtd;
    int *vtx;
    int *dist;
};
typedef struct priorityqueue *queue;

queue createqueue(int);
void enqueue(queue, int, int);
int dequeue(queue);
int isempty(queue);
int isfull(queue);
void printqueue(queue);

queue createqueue(int n)
{
    queue q = malloc(sizeof(struct priorityqueue));
    q->qtd = 0;
    q->vtx = malloc(n * sizeof(int));
    q->dist = malloc(n * sizeof(int));
    return q;
}

void enqueue(queue q, int vtx, int dist)
{
    if (isfull(q))
        return;
    q->vtx[q->qtd] = vtx;
    q->dist[q->qtd] = dist;
    q->qtd++;
}

int dequeue(queue q)
{
    if (isempty(q))
        return -1;
    int min = 0;
    for (int i = 1; i < q->qtd; i++)
        if (q->dist[i] < q->dist[min])
            min = i;
    int vtx = q->vtx[min];
    q->vtx[min] = q->vtx[q->qtd - 1];
    q->dist[min] = q->dist[q->qtd - 1];
    q->qtd--;
    return vtx;
}

int isempty(queue q)
{
    return q->qtd == 0;
}

int isfull(queue q)
{
    return q->qtd == SIZEQUEUE;
}

void printqueue(queue q)
{
    for (int i = 0; i < q->qtd; i++)
        printf("%d ", q->vtx[i]);
    printf("\n");
}

// Cria um novo no
struct no *criano(int v)
{
    struct no *novono = malloc(sizeof(struct no));
    novono->vtx = v;
    novono->next = NULL;
    novono->dist = 0; // distancia para ele sempre é 0
    return novono;
}

// Create a graph
struct Graph *criagraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->adjLists = malloc(vertices * sizeof(struct no *));

    graph->qtd_vtx = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Adiciona uma aresta, ou seja uma ligação entre dois vértices nos dois sentidos
void addaresta(struct Graph *graph, int s, int d, int dist)
{
    // add aresta de s para d
    struct no *novono = criano(d);
    novono->next = graph->adjLists[s];
    graph->adjLists[s] = novono;
    graph->adjLists[s]->dist = dist;

    // add aresta de d para s
    novono = criano(s);
    novono->next = graph->adjLists[d];
    graph->adjLists[d] = novono;
    graph->adjLists[d]->dist = dist;
}

// imprime o grafo
void printgraph(struct Graph *graph)
{
    int v;
    for (v = 0; v < graph->qtd_vtx; v++)
    {
        struct no *temp = graph->adjLists[v];
        printf("\n vtx %d\n: ", v);
        while (temp)
        {
            printf("%d -> ", temp->vtx);
            temp = temp->next;
        }
        printf("\n");
    }
}

// caminho mais curto
int caminho_mais_curto(struct Graph *graph, int s, int d)
{
    int *dist = malloc(graph->qtd_vtx * sizeof(int));
    int *prev = malloc(graph->qtd_vtx * sizeof(int));
    int *visitado = malloc(graph->qtd_vtx * sizeof(int));
    for (int i = 0; i < graph->qtd_vtx; i++)
    {
        dist[i] = INFINITY;
        prev[i] = -1;
        visitado[i] = 0;
    }
    dist[s] = 0;
    queue q = createqueue(graph->qtd_vtx);
    enqueue(q, s, dist[s]);
    while (!isempty(q))
    {
        int u = dequeue(q);
        visitado[u] = 1;
        struct no *temp = graph->adjLists[u];
        while (temp)
        {
            int v = temp->vtx;
            if (!visitado[v])
            {
                int alt = dist[u] + temp->dist;
                if (alt < dist[v])
                {
                    dist[v] = alt;
                    prev[v] = u;
                    enqueue(q, v, dist[v]);
                }
            }
            temp = temp->next;
        }
    }
    int i = d;
    while (prev[i] != -1)
    {
        printf("%d ", i);
        i = prev[i];
    }
    printf("%d\n", i);
    return dist[d];
}

void DFS(struct Graph *graph, int v, int *visitado)
{
    visitado[v] = 1;
    printf("%d ", v);
    struct no *temp = graph->adjLists[v];
    while (temp)
    {
        int adj = temp->vtx;
        if (!visitado[adj])
            DFS(graph, adj, visitado);
        temp = temp->next;
    }
}

int main()
{
    struct Graph *graph = criagraph(4);
    addaresta(graph, 0, 1, 5);
    addaresta(graph, 0, 3, 3);
    addaresta(graph, 1, 2, 1);

    printgraph(graph);

    printf("caminho mais curto: %d -> %d = %d\n", 0, 2, caminho_mais_curto(graph, 0, 2));

    int *visitado = malloc(graph->qtd_vtx * sizeof(int));
    for (int i = 0; i < graph->qtd_vtx; i++)
        visitado[i] = 0;
    printf("DFS: ");
    DFS(graph, 0, visitado);
    printf("\n");
    free(visitado);

    return 0;
}