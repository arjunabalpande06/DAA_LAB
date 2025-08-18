#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Graph representation using adjacency matrix
typedef struct {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Priority queue node for heap implementation
typedef struct {
    int vertex;
    int distance;
} HeapNode;

// Min heap structure
typedef struct {
    HeapNode data[MAX_VERTICES];
    int size;
    int pos[MAX_VERTICES];  // Position of vertex in heap
} MinHeap;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int src);
void dijkstraWithHeap(Graph* graph, int src);
void printPath(int parent[], int dest);
void printResults(int dist[], int parent[], int vertices, int src);

// Basic implementation using simple array (O(V^2))
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    
    // Initialize adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graph->adj[i][j] = 0;
            else
                graph->adj[i][j] = INF;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adj[src][dest] = weight;
}

void addUndirectedEdge(Graph* graph, int src, int dest, int weight) {
    graph->adj[src][dest] = weight;
    graph->adj[dest][src] = weight;
}

int minDistance(int dist[], bool visited[], int vertices) {
    int min = INF, min_index = -1;
    
    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int dest) {
    if (parent[dest] == -1) {
        printf("%d", dest);
        return;
    }
    printPath(parent, parent[dest]);
    printf(" -> %d", dest);
}

void printResults(int dist[], int parent[], int vertices, int src) {
    printf("\nShortest distances from vertex %d:\n", src);
    printf("Vertex\tDistance\tPath\n");
    printf("------\t--------\t----\n");
    
    for (int i = 0; i < vertices; i++) {
        printf("%d\t", i);
        if (dist[i] == INF) {
            printf("INF\t\tNo path\n");
        } else {
            printf("%d\t\t", dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

void dijkstra(Graph* graph, int src) {
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    // Initialize arrays
    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        
        if (u == -1) break;  // No more reachable vertices
        
        visited[u] = true;
        
        // Update distances of adjacent vertices
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && 
                graph->adj[u][v] != INF && 
                dist[u] != INF && 
                dist[u] + graph->adj[u][v] < dist[v]) {
                
                dist[v] = dist[u] + graph->adj[u][v];
                parent[v] = u;
            }
        }
    }
    
    printResults(dist, parent, vertices, src);
}

// Heap-based implementation (more efficient for sparse graphs)
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && heap->data[left].distance < heap->data[smallest].distance)
        smallest = left;
    
    if (right < heap->size && heap->data[right].distance < heap->data[smallest].distance)
        smallest = right;
    
    if (smallest != idx) {
        // Update position array
        heap->pos[heap->data[smallest].vertex] = idx;
        heap->pos[heap->data[idx].vertex] = smallest;
        
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

HeapNode extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        HeapNode empty = {-1, INF};
        return empty;
    }
    
    HeapNode root = heap->data[0];
    HeapNode lastNode = heap->data[heap->size - 1];
    
    heap->data[0] = lastNode;
    heap->pos[lastNode.vertex] = 0;
    heap->pos[root.vertex] = -1;
    
    heap->size--;
    heapify(heap, 0);
    
    return root;
}

void decreaseKey(MinHeap* heap, int vertex, int newDist) {
    int i = heap->pos[vertex];
    heap->data[i].distance = newDist;
    
    // Fix the min heap property if it's violated
    while (i > 0 && heap->data[i].distance < heap->data[(i-1)/2].distance) {
        heap->pos[heap->data[i].vertex] = (i-1)/2;
        heap->pos[heap->data[(i-1)/2].vertex] = i;
        swap(&heap->data[i], &heap->data[(i-1)/2]);
        i = (i-1)/2;
    }
}

bool isInMinHeap(MinHeap* heap, int vertex) {
    return heap->pos[vertex] < heap->size;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    
    for (int i = 0; i < capacity; i++) {
        heap->pos[i] = i;
        heap->data[i].vertex = i;
        heap->data[i].distance = INF;
    }
    
    return heap;
}

void dijkstraWithHeap(Graph* graph, int src) {
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    MinHeap* heap = createMinHeap(vertices);
    
    // Initialize distances and heap
    for (int v = 0; v < vertices; v++) {
        dist[v] = INF;
        parent[v] = -1;
        heap->data[v].distance = INF;
        heap->data[v].vertex = v;
    }
    
    // Set source distance and update heap
    dist[src] = 0;
    heap->data[src].distance = 0;
    heap->size = vertices;
    decreaseKey(heap, src, 0);
    
    while (heap->size > 0) {
        HeapNode minNode = extractMin(heap);
        int u = minNode.vertex;
        
        // Traverse all adjacent vertices of u
        for (int v = 0; v < vertices; v++) {
            if (graph->adj[u][v] != INF && 
                isInMinHeap(heap, v) && 
                dist[u] != INF && 
                dist[u] + graph->adj[u][v] < dist[v]) {
                
                dist[v] = dist[u] + graph->adj[u][v];
                parent[v] = u;
                decreaseKey(heap, v, dist[v]);
            }
        }
    }
    
    printResults(dist, parent, vertices, src);
    free(heap);
}

// Function to find shortest path between two specific vertices
int findShortestPath(Graph* graph, int src, int dest, int path[]) {
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    // Initialize
    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        
        if (u == -1 || u == dest) break;  // Early termination
        
        visited[u] = true;
        
        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && 
                graph->adj[u][v] != INF && 
                dist[u] != INF && 
                dist[u] + graph->adj[u][v] < dist[v]) {
                
                dist[v] = dist[u] + graph->adj[u][v];
                parent[v] = u;
            }
        }
    }
    
    // Reconstruct path
    if (dist[dest] == INF) {
        return -1;  // No path found
    }
    
    int pathLength = 0;
    int current = dest;
    int tempPath[MAX_VERTICES];
    
    // Build path in reverse
    while (current != -1) {
        tempPath[pathLength++] = current;
        current = parent[current];
    }
    
    // Reverse the path
    for (int i = 0; i < pathLength; i++) {
        path[i] = tempPath[pathLength - 1 - i];
    }
    
    return pathLength;
}

// Example usage and test cases
int main() {
    printf("Dijkstra's Algorithm Implementation in C\n");
    printf("========================================\n\n");
    
    // Example 1: Simple directed graph
    printf("Example 1: Simple Directed Graph\n");
    printf("---------------------------------\n");
    
    Graph* graph1 = createGraph(6);
    
    addEdge(graph1, 0, 1, 4);
    addEdge(graph1, 0, 2, 2);
    addEdge(graph1, 1, 2, 1);
    addEdge(graph1, 1, 3, 5);
    addEdge(graph1, 2, 3, 8);
    addEdge(graph1, 2, 4, 10);
    addEdge(graph1, 3, 4, 2);
    addEdge(graph1, 3, 5, 6);
    addEdge(graph1, 4, 5, 3);
    
    printf("Using basic O(V^2) implementation:\n");
    dijkstra(graph1, 0);
    
    printf("\nUsing heap-based O((V+E)logV) implementation:\n");
    dijkstraWithHeap(graph1, 0);
    
    // Example 2: Find specific shortest path
    printf("\n\nExample 2: Specific Path Finding\n");
    printf("--------------------------------\n");
    
    int path[MAX_VERTICES];
    int pathLength = findShortestPath(graph1, 0, 5, path);
    
    if (pathLength > 0) {
        printf("Shortest path from 0 to 5: ");
        for (int i = 0; i < pathLength; i++) {
            printf("%d", path[i]);
            if (i < pathLength - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("No path found from 0 to 5\n");
    }
    
    // Example 3: Undirected graph
    printf("\n\nExample 3: Undirected Graph\n");
    printf("---------------------------\n");
    
    Graph* graph2 = createGraph(5);
    
    addUndirectedEdge(graph2, 0, 1, 2);
    addUndirectedEdge(graph2, 0, 3, 6);
    addUndirectedEdge(graph2, 1, 2, 3);
    addUndirectedEdge(graph2, 1, 3, 8);
    addUndirectedEdge(graph2, 1, 4, 5);
    addUndirectedEdge(graph2, 2, 4, 7);
    addUndirectedEdge(graph2, 3, 4, 9);
    
    dijkstra(graph2, 0);
    
    // Cleanup
    free(graph1);
    free(graph2);
    
    printf("\n\nComplexity Analysis:\n");
    printf("-------------------\n");
    printf("Basic implementation: O(V^2)\n");
    printf("Heap implementation:  O((V + E) log V)\n");
    printf("Space complexity:     O(V)\n");
    printf("\nBest for dense graphs: Basic implementation\n");
    printf("Best for sparse graphs: Heap implementation\n");
    
    return 0;
}
