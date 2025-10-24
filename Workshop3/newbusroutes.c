#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // Standard library functions, including dynamic memory allocation
#include <limits.h>     // Provides INT_MAX, which we use to represent infinity
#define INF INT_MAX     // Define infinity as the largest possible integer value (used for unprocessed nodes in Dijkstra) //marco
// Function to find the node with the minimum distance that hasn't been processed yet
int min_distance(int dist[], int processed[], int n) 
{
    int min = INF;      // Start with an infinite min distance
    int min_index = -1; // Initialize the index of the node with the minimum distance
    // Iterate through all nodes to find the one with the smallest distance
    for (int v = 0; v < n; v++) {
        if (!processed[v] && dist[v] <= min) {  // Only consider unprocessed nodes
            min = dist[v];     // Update the minimum distance
            min_index = v;     // Update the index of the node with the minimum distance
        }
    }
    return min_index;  // Return the index of the node with the minimum distance
}
// Dijkstra's algorithm to find the shortest paths from the airport (node 0)
// graph: The adjacency matrix representing the train network
// n: The number of nodes in the graph
// dist: Array to store the shortest distance from the airport to each node
void dijkstra(int **graph, int n, int dist[]) 
{
    int processed[n];  // Array to track whether each node has been processed (1 = processed, 0 = unprocessed)

    // Initialize all distances to infinity and mark all nodes as unprocessed
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;     // Set initial distance to infinity for all nodes
        processed[i] = 0;  // Initially mark all nodes as unprocessed
    }
    dist[0] = 0;  // Set the distance to the source node (airport)
    // Process all nodes in the graph
    for (int count = 0; count < n - 1; count++) // go through all the nodes
    {
        // Find the unprocessed node with the smallest distance
        int u = min_distance(dist, processed, n);
        // Mark the picked node as processed
        processed[u] = 1;
        // Update the distances to the adjacent nodes of the picked node
        for (int v = 0; v < n; v++) 
        {
            // Update the distance to node v only if it's unprocessed, there is a direct edge from u to v,
            // and the new distance through u is smaller than the previously known distance
            if (!processed[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];  // Update the shortest distance to node v
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the user has provided exactly two command-line arguments (train file and bus file)
    if (argc != 3) {
                return 1;  // Exit
    }

    // Open the train routes file for reading
    FILE *train_file = fopen(argv[1], "r");
    if (!train_file) {  // If the file cannot be opened
            return 1;
    }

    // Read the number of nodes in the transportation graph from the first line of the file
    int n;
    fscanf(train_file, "%d", &n);

    // Dynamically allocate memory for the adjacency matrix of the train network
    int **train_graph = (int **)malloc(n * sizeof(int *));  // Create an array of pointers for the rows
    for (int i = 0; i < n; i++) 
    {
        train_graph[i] = (int *)malloc(n * sizeof(int));     // Allocate memory for each row (each row represents a node)
    }

    // Read the adjacency matrix from the train file, where each row corresponds to one node's connections
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(train_file, "%d", &train_graph[i][j]);    // Read each integer into the adjacency matrix
        }
    }
    fclose(train_file);  // Close the train file after reading the data

    // Allocate memory to store the shortest distances from the airport (node 0)
    int *train_times = (int *)malloc(n * sizeof(int));  // Create an array to store the shortest time to each node
    // Call Dijkstra's algorithm to compute the shortest times from the airport to all nodes
    dijkstra(train_graph, n, train_times);
    // Open the proposed bus routes file for reading
    FILE *bus_file = fopen(argv[2], "r");
    if (!bus_file) {  // If the file cannot be opened, print an error message and exit
        return 1;
    }
    // Read the number of proposed bus routes from the first line of the file
    int num_buses;
    fscanf(bus_file, "%d", &num_buses);
    // For each proposed bus route, read the destination and bus travel time and compare with the shortest train time
    for (int i = 0; i < num_buses; i++) {
        int destination, bus_time;
        fscanf(bus_file, "%d %d", &destination, &bus_time);  // Read the destination node and bus time

        // Compare the bus time to the shortest train time for the same destination
        if (bus_time < train_times[destination]) {
            // If the bus time is shorter, output the destination node
            printf("%d\n", destination);
        }
    }
    fclose(bus_file);  // Close the bus file after reading the data
    // Free the dynamically allocated memory for the train times array
    free(train_times);
    // Free the memory allocated for the adjacency matrix
    for (int i = 0; i < n; i++) {
        free(train_graph[i]);  // Free each row
    }
    free(train_graph);  // Free the array of pointers
    return 0;  // Return success
}
