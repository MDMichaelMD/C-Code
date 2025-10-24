// graph.c

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Initialize the graph by setting the head node to NULL
Graph* initializeGraph() {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (graph == NULL) {
        exit(1);
    }else{
       graph->headNode = NULL;
    }
    return graph;
}

// Free all memory and delete the graph
void deleteGraph(Graph* myGraph) {
    Node* current = myGraph->headNode;
    while (current != NULL) {
      // Delete the nodes's edges
        Node* tempNode = current;
        Edge* currentEdge = current->edges;
        while (currentEdge != NULL) {
            Edge* tempEdge = currentEdge;
            currentEdge = currentEdge->nextEdge;
            free(tempEdge);
        }
        current = current->nextNode;
        free(tempNode);
    }
    // when current = null, free the whole graph
    free(myGraph);
}

// Add a node to the graph
void addNode(Graph* myGraph, int myNodeID) {
    // Check if the node already exists
    Node* current = myGraph->headNode;
    Node* newNode = (Node*) malloc(sizeof(Node));
    while (current != NULL) {
        if (current->nodeID == myNodeID) {
            return;
        }
        current = current->nextNode;
    }
    if (newNode == NULL) {
        exit(1);
    }
    newNode->nodeID = myNodeID;
    newNode->edges = NULL;
    newNode->nextNode = myGraph->headNode;
    myGraph->headNode = newNode;
}

// Add an edge between two nodes
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeweight) {
    Node* fromNode = myGraph->headNode;
    while (fromNode != NULL && fromNode->nodeID != myFromNodeID) {
        fromNode = fromNode->nextNode;
    }
    if (fromNode == NULL) {
        return;
    }

    // Create a new edge
    Edge* newEdge = (Edge*) malloc(sizeof(Edge));
    if (newEdge == NULL) {
        exit(1);
    }
    newEdge->toNodeID = myToNodeID;
    newEdge->weight = myEdgeweight;
    newEdge->nextEdge = fromNode->edges;  // Add edge at the start of the adjacency list
    fromNode->edges = newEdge;
}

// Delete a node and the edges
void deleteNode(Graph* myGraph, int myNodeID) {
    Node* current = myGraph->headNode;
    Node* previous = NULL;
    Node* tempNode = myGraph->headNode;

    // Find the node to delete
    while (current != NULL && current->nodeID != myNodeID) {
        previous = current;
        current = current->nextNode;
    }
    if (current == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    Edge* currentEdge = current->edges;
    while (currentEdge != NULL) {
        Edge* tempEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
        free(tempEdge);
    }
    current->edges = NULL;

    while (tempNode != NULL) {
        Edge* prevEdge = NULL;
        Edge* tempEdge = tempNode->edges;
        while (tempEdge != NULL) {
            if (tempEdge->toNodeID == myNodeID) {
                if (prevEdge == NULL) {
                    tempNode->edges = tempEdge->nextEdge;
                } else {
                    prevEdge->nextEdge = tempEdge->nextEdge;
                }
                free(tempEdge);
                tempEdge = NULL;
                break;
            }
            prevEdge = tempEdge;
            tempEdge = tempEdge->nextEdge;
        }
        tempNode = tempNode->nextNode;
    }

    // Remove the node from the list
    if (previous == NULL) {
        myGraph->headNode = current->nextNode;
    } else {
        previous->nextNode = current->nextNode;
    }
    free(current);
    current = NULL;
}

// Delete an edge between two nodes
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID) {
    Node* fromNode = myGraph->headNode;

    while (fromNode != NULL && fromNode->nodeID != myFromNodeID) {
        fromNode = fromNode->nextNode;
    }
    if (fromNode == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    Edge* currentEdge = fromNode->edges;
    Edge* previousEdge = NULL;

    while (currentEdge != NULL && currentEdge->toNodeID != myToNodeID) {
        previousEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
    }
    if (currentEdge == NULL) {
        deleteGraph(myGraph);
        exit(1);
    }

    // Remove the edge from the adjacency list
    if (previousEdge == NULL) {
        fromNode->edges = currentEdge->nextEdge;
    } else {
        previousEdge->nextEdge = currentEdge->nextEdge;
    }
    free(currentEdge);
}

// Calculate the number of nodes in the graph
int calcNumNodes(Graph* myGraph) {
    int count = 0;
    Node* current = myGraph->headNode;
    while (current != NULL) {
        count++;
        current = current->nextNode;
    }
    return count;
}

// Calculate the number of edges in the graph
int calcNumEdges(Graph* myGraph) {
    int count = 0;
    Node* current = myGraph->headNode;
    while (current != NULL) {
        Edge* currentEdge = current->edges;
        while (currentEdge != NULL) {
            count++;
            currentEdge = currentEdge->nextEdge;
        }
        current = current->nextNode;
    }
    return count;
}

// Print the list of nodes
void printNodeList(Graph* myGraph) {
    Node* current = myGraph->headNode;
    while (current != NULL) {
        printf("%d ", current->nodeID);
        current = current->nextNode;
    }
    printf("\n");
}

 // Print the list of edges
void printEdgeList(Graph* myGraph) {
    Node* current = myGraph->headNode;
    while (current != NULL) {
        Edge* currentEdge = current->edges;
        while (currentEdge != NULL) {
            printf("(%d, %d, %.6f)", current->nodeID, currentEdge->toNodeID, currentEdge->weight);
            currentEdge = currentEdge->nextEdge;
            if (currentEdge != NULL) {
                printf("\n");
            }
        }
        if (current->edges != NULL) {
            printf("\n"); 
        }
        current = current->nextNode;
    }
}

