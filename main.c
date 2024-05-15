#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para representar o grafo com matriz de adjacências
typedef struct {
    int numVertices;
    int** adjMatrix;
} Graph;

// Função para criar um grafo com 'numVertices' vértices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(numVertices, sizeof(int)); // Inicializa com 0 (sem aresta)
    }

    return graph;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        graph->adjMatrix[src][dest] = 1;
        graph->adjMatrix[dest][src] = 1; // Se o grafo for não direcionado
    } else {
        printf("Erro: Vértices inválidos.\n");
    }
}

// Função para realizar a busca em largura
void BFS(const Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = startVertex;
    visited[startVertex] = true;

    printf("Resultado da Busca em Largura (BFS):\n");

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }

    printf("\n");

    free(visited);
    free(queue);
}

// Função para imprimir o grafo
void printGraph(const Graph* graph) {
    printf("Matriz de Adjacências:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Função para liberar a memória alocada para o grafo
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

int main() {
    int numVertices;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    Graph* graph = createGraph(numVertices);

    int choice, src, dest;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar aresta\n");
        printf("2. Realizar Busca em Largura (BFS)\n");
        printf("3. Imprimir grafo\n");
        printf("4. Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o vértice de origem: ");
                scanf("%d", &src);
                printf("Digite o vértice de destino: ");
                scanf("%d", &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                printf("Digite o vértice de início da Busca em Largura (BFS): ");
                scanf("%d", &src);
                if (src >= 0 && src < graph->numVertices) {
                    printf("Resultado da Busca em Largura (BFS) a partir do vértice %d:\n", src);
                    BFS(graph, src);
                } else {
                    printf("Erro: Vértice de início inválido.\n");
                }
                break;
            case 3:
                printGraph(graph);
                break;
            case 4:
                freeGraph(graph);
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
