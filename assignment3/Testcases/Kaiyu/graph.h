#pragma once

// Define the structure for edges (adjacency list of a node)
typedef struct Edge {
    int toNodeID;               // The ID of the destination node
    double weight;              // The weight of the edge
    struct Edge* nextEdge;      // Pointer to the next edge in the adjacency list
} Edge;

// Define the structure for nodes (vertices in the graph)
typedef struct Node {
    int nodeID;                 // The ID of the node
    struct Edge* adjList;       // Pointer to the head of the adjacency list (edges)
    struct Node* nextNode;      // Pointer to the next node in the graph
} Node;

// Define the structure for the graph
typedef struct Graph {
    struct Node* headNode;      // Pointer to the first node in the graph
} Graph;

// Function declarations
Graph* initializeGraph();
void deleteGraph(Graph* myGraph);
void addNode(Graph* myGraph, int myNodeID);
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeWeight);
void deleteNode(Graph* myGraph, int myNodeID);
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID);
int calcNumNodes(Graph* myGraph);
int calcNumEdges(Graph* myGraph);
void printNodeList(Graph* myGraph);
void printEdgeList(Graph* myGraph);
