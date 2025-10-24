#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    // Initialize the graph
    Graph* myGraph = initializeGraph();

    // Add nodes to the graph
    addNode(myGraph, 2);
    addNode(myGraph, 7);
    addNode(myGraph, 3);
    addNode(myGraph, 5);
    addNode(myGraph, 9);

    // Add edges between nodes
    addEdge(myGraph, 2, 7, 0.5);
    addEdge(myGraph, 3, 5, 0.5);
    addEdge(myGraph, 3, 9, 2.4);
    addEdge(myGraph, 7, 5, 10.9);

    // Print the list of nodes
    printf("Node list:\n");
    printNodeList(myGraph);

    // Print the list of edges
    printf("Edge list:\n");
    printEdgeList(myGraph);

    // Calculate and print the number of nodes and edges
    printf("Number of nodes: %d\n", calcNumNodes(myGraph));
    printf("Number of edges: %d\n", calcNumEdges(myGraph));

    // Clean up and delete the graph
    deleteGraph(myGraph);

    return 0;
}
