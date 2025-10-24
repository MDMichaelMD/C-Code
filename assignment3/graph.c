#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Initialize an empty graph
Graph* initializeGraph() {
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    if (!newGraph) return NULL;
    newGraph->nodeList = NULL;
    return newGraph;
}

// Find a node by its ID
Node* findNode(Graph* myGraph, int nodeID) {
    Node* currentNode = myGraph->nodeList;
    while (currentNode != NULL) {
        if (currentNode->nodeID == nodeID) return currentNode;
        currentNode = currentNode->nextNode;
    }
    return NULL;
}

// Add a node to the graph
void addNode(Graph* myGraph, int myNodeID) {
    if (findNode(myGraph, myNodeID) != NULL) return; // Node already exists

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return; // Memory allocation failure
    newNode->nodeID = myNodeID;
    newNode->adjacencyList = NULL;
    newNode->nextNode = myGraph->nodeList;
    myGraph->nodeList = newNode;
}

// Add an edge between two nodes
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeWeight) {
    Node* fromNode = findNode(myGraph, myFromNodeID);
    Node* toNode = findNode(myGraph, myToNodeID);

    if (!fromNode || !toNode) return; // Either fromNode or toNode doesn't exist

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return; // Memory allocation failure
    newEdge->toNodeID = myToNodeID;
    newEdge->edgeWeight = myEdgeWeight;
    newEdge->nextEdge = fromNode->adjacencyList;
    fromNode->adjacencyList = newEdge;
}

// Delete a node from the graph
void deleteNode(Graph* myGraph, int myNodeID) {
    Node* prevNode = NULL;
    Node* currentNode = myGraph->nodeList;

    // Find the node to delete
    while (currentNode != NULL) {
        if (currentNode->nodeID == myNodeID) {
            // First, delete all edges that originate from this node
            while (currentNode->adjacencyList != NULL) {
                deleteEdge(myGraph, myNodeID, currentNode->adjacencyList->toNodeID);
            }

            // Now, delete all edges that terminate at this node
            Node* tempNode = myGraph->nodeList;
            while (tempNode != NULL) {
                // Check if tempNode has any edges that terminate at myNodeID
                Edge* tempEdge = tempNode->adjacencyList;
                while (tempEdge != NULL) {
                    if (tempEdge->toNodeID == myNodeID) {
                        deleteEdge(myGraph, tempNode->nodeID, myNodeID); // Delete the edge that points to this node
                        break; // Move to the next node after deleting the edge
                    }
                    tempEdge = tempEdge->nextEdge;
                }
                tempNode = tempNode->nextNode;
            }

            // Remove the node from the graph's node list
            if (prevNode == NULL) {
                myGraph->nodeList = currentNode->nextNode;
            } else {
                prevNode->nextNode = currentNode->nextNode;
            }

            free(currentNode); // Free the node's memory
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->nextNode;
    }

    // Node not found, exit with error code 1
    exit(1);
}

/*
void deleteNode(Graph* myGraph, int myNodeID) {
    Node* prevNode = NULL;
    Node* currentNode = myGraph->nodeList;

    while (currentNode != NULL)
    {
        if (currentNode->nodeID == myNodeID) //or !=nyN//if it doesnt match the input check the h has a matching idea]
         {
            // First, delete all edges associated with this node
            while (currentNode->adjacencyList != NULL) {
                deleteEdge(myGraph, myNodeID, currentNode->adjacencyList->toNodeID);
            }

            // Remove the node from the graph's node list
            if (prevNode == NULL) {
                myGraph->nodeList = currentNode->nextNode;
            } else {
                prevNode->nextNode = currentNode->nextNode;
            }
            free(currentNode);
            return;
        }
        else //(currentNode->nodeID != myNodeID) // check if there is an H between current to node id and if so delete it
       {
        
       }
        prevNode = currentNode;
        currentNode = currentNode->nextNode;
    }
    
    // Node not found, exit with error code 1
    exit(1);
}
*/
// Delete an edge between two nodes
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID) {
    Node* fromNode = findNode(myGraph, myFromNodeID);
    if (!fromNode) exit(1); // Node does not exist, exit with error code 1

    Edge* prevEdge = NULL;
    Edge* currentEdge = fromNode->adjacencyList;

    while (currentEdge != NULL) {
        if (currentEdge->toNodeID == myToNodeID) {
            // Edge found, delete it
            if (prevEdge == NULL) {
                fromNode->adjacencyList = currentEdge->nextEdge;
            } else {
                prevEdge->nextEdge = currentEdge->nextEdge;
            }
            free(currentEdge);
            return;
        }
        prevEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
    }
    
    // Edge not found, exit with error code 1
    exit(1);
}

// Calculate the number of nodes in the graph
int calcNumNodes(Graph* myGraph) {
    int count = 0;
    Node* currentNode = myGraph->nodeList;
    while (currentNode != NULL) {
        count++;
        currentNode = currentNode->nextNode;
    }
    return count;
}

// Calculate the number of edges in the graph
int calcNumEdges(Graph* myGraph) {
    int count = 0;
    Node* currentNode = myGraph->nodeList;
    while (currentNode != NULL) {
        Edge* currentEdge = currentNode->adjacencyList;
        while (currentEdge != NULL) {
            count++;
            currentEdge = currentEdge->nextEdge;
        }
        currentNode = currentNode->nextNode;
    }
    return count;
}

// Print the list of nodes
void printNodeList(Graph* myGraph) {
    Node* currentNode = myGraph->nodeList;
    while (currentNode != NULL) {
        printf("%d ", currentNode->nodeID);
        currentNode = currentNode->nextNode;
    }
    printf("\n");
}

// Print the list of edges
void printEdgeList(Graph* myGraph) {
    Node* currentNode = myGraph->nodeList;
    while (currentNode != NULL) {
        Edge* currentEdge = currentNode->adjacencyList;
        while (currentEdge != NULL) {
            // Ensure the output is formatted correctly and all edges are printed
            printf("(%d, %d, %f)\n", currentNode->nodeID, currentEdge->toNodeID, currentEdge->edgeWeight);
            currentEdge = currentEdge->nextEdge;
        }
        currentNode = currentNode->nextNode;
    }
}

// Delete the entire graph
void deleteGraph(Graph* myGraph) {
    while (myGraph->nodeList != NULL) {
        deleteNode(myGraph, myGraph->nodeList->nodeID);
    }
    free(myGraph);
}
