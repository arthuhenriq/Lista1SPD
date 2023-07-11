#include <stdio.h>
#include <omp.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

void dfs(int vertex) {
    printf("Visitando vértice %d\n", vertex);
    visited[vertex] = 1;

    // Itera sobre todos os vértices adjacentes
    #pragma omp parallel for
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int num_vertices, start_vertex;

    // Leitura do número de vértices e vértice inicial
    printf("Digite o número de vértices: ");
    scanf("%d", &num_vertices);
    printf("Digite o vértice inicial: ");
    scanf("%d", &start_vertex);

    // Leitura da matriz de adjacência
    printf("Digite a matriz de adjacência:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Inicialização do vetor de visitados
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
    }

    // Chama a função DFS no vértice inicial
    dfs(start_vertex);

    return 0;
}
