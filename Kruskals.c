#include <stdio.h>
#include <limits.h>

#define MAX 100   // Maximum number of vertices

void primMST(int graph[MAX][MAX], int n) {
    int parent[MAX];  // To store constructed MST
    int key[MAX];     // To pick minimum weight edge in cut
    int mstSet[MAX];  // To represent set of vertices included in MST
    int i, count, u, v;

    // Initialize all keys as infinite
    for (i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0; // Initially, no vertex is included in MST
    }

    // Always include first vertex in MST
    key[0] = 0;      // Make key 0 so that this vertex is picked first
    parent[0] = -1;  // First node is root of MST

    // The MST will have n vertices
    for (count = 0; count < n - 1; count++) {
        // Find the vertex u not yet included in MST with min key value
        int min = INT_MAX;
        for (v = 0; v < n; v++)
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        // Add the picked vertex to the MST set
        mstSet[u] = 1;

        // Update key and parent for adjacent vertices
        for (v = 0; v < n; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    // Print the constructed MST
    printf("\nEdges in the Minimum Cost Spanning Tree:\n");
    int totalCost = 0;
    for (i = 1; i < n; i++) {
        printf("%d - %d  (Cost: %d)\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    printf("Total Minimum Cost: %d\n", totalCost);
}

int main() {
    int n, i, j;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, n);

    return 0;
}
