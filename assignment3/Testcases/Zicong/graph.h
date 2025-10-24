// graph.h

// Struct to represent an Edge in the adjacency list
typedef struct edge {
    int toNodeID;              // ID of the destination node
    double weight;             // Weight of the edge
    struct edge* nextEdge;     // Pointer to the next edge in the adjacency list
} Edge;

// Struct to represent a Node in the graph
typedef struct node {
    int nodeID;                // ID of the node
    Edge* edges;               // Pointer to the list of edges (adjacency list)
    struct node* nextNode;     // Pointer to the next node in the node list
} Node;

// Struct to represent the Graph
typedef struct graph {
    Node* headNode;            // Pointer to the first node in the graph
} Graph;

// Function declarations
Graph* initializeGraph();
void deleteGraph(Graph* myGraph);
void addNode(Graph* myGraph, int myNodeID);
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeweight);
void deleteNode(Graph* myGraph, int myNodeID);
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID);
int calcNumNodes(Graph* myGraph);
int calcNumEdges(Graph* myGraph);
void printNodeList(Graph* myGraph);
void printEdgeList(Graph* myGraph);


