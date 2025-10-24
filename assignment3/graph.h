#ifndef GRAPH_H
#define GRAPH_H

// Struct to represent an edge in the graph's adjacency list
typedef struct Edge {
    int toNodeID;              // ID of the destination node
    double edgeWeight;         // Weight of the edge
    struct Edge* nextEdge;     // Pointer to the next edge in the adjacency list
} Edge;

// Struct to represent a node in the graph
typedef struct Node {
    int nodeID;                // ID of the node
    Edge* adjacencyList;       // Pointer to the list of edges from this node
    struct Node* nextNode;     // Pointer to the next node in the graph
} Node;

// Struct to represent the graph itself
typedef struct Graph {
    Node* nodeList;            // Pointer to the list of nodes in the graph
} Graph;

// Function declarations for graph operations
Graph* initializeGraph();                                   // Initializes an empty graph
void deleteGraph(Graph* myGraph);                           // Deletes the entire graph
void addNode(Graph* myGraph, int myNodeID);                 // Adds a node to the graph
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeweight); // Adds an edge
void deleteNode(Graph* myGraph, int myNodeID);              // Deletes a node from the graph
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID); // Deletes an edge
int calcNumNodes(Graph* myGraph);                          // Returns the number of nodes
int calcNumEdges(Graph* myGraph);                          // Returns the number of edges
void printNodeList(Graph* myGraph);                        // Prints the list of nodes
void printEdgeList(Graph* myGraph);                        // Prints the list of edges

#endif // GRAPH_H
