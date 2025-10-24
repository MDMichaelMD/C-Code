#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Helper function to find a node by ID
Node* findNode(Graph* myGraph, int nodeID) {
    Node* current = myGraph->headNode;
    while (current != NULL && current->nodeID != nodeID) {
        current = current->nextNode;
    }
    return current; // Returns NULL if node not found
}

// Function to initialize a new graph
Graph* initializeGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->headNode = NULL;  // Set the headNode pointer to NULL initially
    return graph;
}

// Function to delete all edges of a node
void deleteEdgesOfNode(Node* node) {
    Edge* currentEdge = node->adjList;
    while (currentEdge != NULL) {
        Edge* nextEdge = currentEdge->nextEdge;
        free(currentEdge);
        currentEdge = nextEdge;
    }
}

// Function to delete the entire graph and free memory
void deleteGraph(Graph* myGraph) {
    Node* current = myGraph->headNode;
    while (current != NULL) {
        Node* nextNode = current->nextNode;
        deleteEdgesOfNode(current); // Delete all edges of the current node
        free(current); // Free the node itself
        current = nextNode;
    }
    free(myGraph); // Free the graph structure
}

// Function to add a node to the graph
void addNode(Graph* myGraph, int myNodeID) {
    if (findNode(myGraph, myNodeID) != NULL) {
        printf("Node with ID %d already exists.\n", myNodeID);
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nodeID = myNodeID;
    newNode->adjList = NULL;
    newNode->nextNode = myGraph->headNode;
    myGraph->headNode = newNode;
}

// Function to add an edge to the graph
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeWeight) {
    Node* fromNode = findNode(myGraph, myFromNodeID);
    Node* toNode = findNode(myGraph, myToNodeID);

    if (fromNode == NULL || toNode == NULL) {
        printf("One or both nodes do not exist. Cannot add edge.\n");
        return;
    }

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->toNodeID = myToNodeID;
    newEdge->weight = myEdgeWeight;
    newEdge->nextEdge = fromNode->adjList;
    fromNode->adjList = newEdge;
}

// Function to delete a node from the graph
void deleteNode(Graph* myGraph, int myNodeID) {
    Node* current = myGraph->headNode;
    Node* prev = NULL;

    // Traverse to find the node to delete
    while (current != NULL && current->nodeID != myNodeID) {
        prev = current;
        current = current->nextNode;
    }

    if (current == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    // Delete all edges associated with this node
    deleteEdgesOfNode(current);

    // Remove node from the list
    if (prev == NULL) {
        myGraph->headNode = current->nextNode;  // Node to delete is the head
    } else {
        prev->nextNode = current->nextNode;     // Node to delete is in the middle or end
    }

    free(current);  // Free the node memory
}

// Function to delete an edge from the graph
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID) {
    Node* fromNode = findNode(myGraph, myFromNodeID);

    if (fromNode == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    Edge* currentEdge = fromNode->adjList;
    Edge* prevEdge = NULL;

    // Traverse to find the edge to delete
    while (currentEdge != NULL && currentEdge->toNodeID != myToNodeID) {
        prevEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
    }

    if (currentEdge == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    // Remove edge from adjacency list
    if (prevEdge == NULL) {
        fromNode->adjList = currentEdge->nextEdge;  // Edge to delete is head of adjList
    } else {
        prevEdge->nextEdge = currentEdge->nextEdge; // Edge to delete is in the middle or end
    }

    free(currentEdge);  // Free the edge memory
}

// Function to calculate the number of nodes in the graph
int calcNumNodes(Graph* myGraph) {
    Node* current = myGraph->headNode;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->nextNode;
    }

    return count;
}

// Function to calculate the number of edges in the graph
int calcNumEdges(Graph* myGraph) {
    Node* current = myGraph->headNode;
    int count = 0;

    while (current != NULL) {
        Edge* edgeCurrent = current->adjList;
        while (edgeCurrent != NULL) {
            count++;
            edgeCurrent = edgeCurrent->nextEdge;
        }
        current = current->nextNode;
    }

    return count;
}

// Function to print the list of node IDs in the graph
void printNodeList(Graph* myGraph) {
    Node* current = myGraph->headNode;

    while (current != NULL) {
        printf("%d ", current->nodeID);
        if (current->nextNode != NULL) {
            printf(" ");  // Print a space nodes
        }
        current = current->nextNode;
    }
    printf("\n");
}

// Function to print the list of edges in the graph
void printEdgeList(Graph* myGraph) {
    Node* current = myGraph->headNode;

    while (current != NULL) {
        Edge* edgeCurrent = current->adjList;
        while (edgeCurrent != NULL) {
            printf("(%d, %d, %f)\n", current->nodeID, edgeCurrent->toNodeID, edgeCurrent->weight);
            edgeCurrent = edgeCurrent->nextEdge;
        }
        current = current->nextNode;
    }
}

