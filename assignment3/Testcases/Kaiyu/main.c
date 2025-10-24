// graphs program: dynamic graph management
#include <stdio.h>
#include "graph.h"

int main(int argc, char *argv[]) {
    Graph* graph = initializeGraph();

    // Adding nodes
    addNode(graph, 1);
    addNode(graph, 2);
    addNode(graph, 3);
    addNode(graph, 4);
    printf("Number of nodes: %d; number of edges: %d\n", calcNumNodes(graph), calcNumEdges(graph));
    printNodeList(graph);

    // Adding edges
    addEdge(graph, 1, 2, 2.4);
    addEdge(graph, 2, 3, 18.7);
    addEdge(graph, 4, 3, 6.3);
    addEdge(graph, 2, 1, 77.5);
    addEdge(graph, 2, 4, 0.9);
    printf("Number of nodes: %d; number of edges: %d\n", calcNumNodes(graph), calcNumEdges(graph));
    printEdgeList(graph);

    // Deleting an edge
    deleteEdge(graph, 2, 1);
    printf("After deleting edge (2 -> 1):\n");
    printf("Number of nodes: %d; number of edges: %d\n", calcNumNodes(graph), calcNumEdges(graph));
    printEdgeList(graph);

    // Deleting a node
    deleteNode(graph, 3);
    printf("After deleting node 3:\n");
    printf("Number of nodes: %d; number of edges: %d\n", calcNumNodes(graph), calcNumEdges(graph));
    printNodeList(graph);
    printEdgeList(graph);

    // Adding another node and edge
    addNode(graph, 5);
    addEdge(graph, 4, 5, 4.2);
    printf("After adding node 5 and edge (4 -> 5):\n");
    printf("Number of nodes: %d; number of edges: %d\n", calcNumNodes(graph), calcNumEdges(graph));
    printNodeList(graph);
    printEdgeList(graph);

    // Final graph deletion
    deleteGraph(graph);

    return 0;
}

