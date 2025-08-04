#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF 99999

int graph[MAX][MAX], visited[MAX], n;

int findMinVertex(int key[], int visited[]) {
    int min = INF, minIndex;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void primMST() {
    int parent[MAX];   // Array to store constructed MST
    int key[MAX];      // Key values used to pick minimum weight edge
    for (int i = 0; i < n; i++) {
        key[i] = INF;
        visited[i] = 0;
    }

    key[0] = 0;       // Start from vertex 0
    parent[0] = -1;   // First node is always root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = findMinVertex(key, visited);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0)
                graph[i][j] = INF; // Replace 0 with INF for no edge
        }
    }

    primMST();

    return 0;
}
