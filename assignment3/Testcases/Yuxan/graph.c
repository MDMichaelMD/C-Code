#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// an edge contains to-node id, to-node weight and a pointer to the next edge
struct edge{
    int toNodeID;
    double toNodeWeight;
    Edge* NextEdge;
};

// a node contains the node id, a pointer to its edge list, and a pointer to the next node
struct node {
    int nodeID;
    Edge* edgeInfo;
    Node* nextNode;
};

// a graph contains a pointer to the node list
struct graph {
    Node* head;
};


// initialize a new graph
Graph* initializeGraph(){
    Graph* myGraph = (Graph*)malloc(sizeof(Graph));

    // add a null head node to the node list
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode != NULL){
        newNode->nodeID = -1;
        newNode->edgeInfo = NULL;
        newNode->nextNode = NULL;
    }

    if (myGraph != NULL) {
        myGraph->head = newNode;
    }    
    return myGraph;
}


// delete the whole graph and free the memory
void deleteGraph(Graph* myGraph){
    if(myGraph == NULL) {
        return;
    }

    Node* currentNode = myGraph->head;
    Node* tempNode;

    // free all the nodes in the graph
    while(currentNode != NULL){
        tempNode = currentNode;
        currentNode = currentNode->nextNode;
        
        //free all the edges in each node
        Edge* currentEdge = tempNode->edgeInfo;
        Edge* tempEdge;
        while(currentEdge != NULL){
            tempEdge = currentEdge;
            currentEdge = currentEdge->NextEdge;
            free(tempEdge);
        }
        free(tempNode);
    }

    // free the graph stucture itself
    free(myGraph);
}

// add a node to the graph
void addNode(Graph* myGraph, int myNodeID){
    if(myGraph == NULL){
        printf("No graph structure, Please initialize one");
        exit(1);
    }
    
    // create a new node structure
    Node* newNode = (Node*)malloc(sizeof(Node));
    Edge* dummyhead = (Edge*)malloc(sizeof(Edge));
    if(dummyhead != NULL){
        dummyhead->toNodeID = -1;
        dummyhead->toNodeWeight = 0;
        dummyhead->NextEdge = NULL;
    }
    if(newNode != NULL){
        newNode->nodeID = myNodeID;
        newNode->edgeInfo = dummyhead; // add a dummyhead to the edge list of the new node
        newNode->nextNode = NULL;
    }
    
    // add the new node to the end of node list
    Node* currentNode = myGraph->head;
    while(currentNode->nextNode != NULL){
        currentNode = currentNode->nextNode;
    }
    currentNode->nextNode = newNode;

}

// add an edge to the graph
void addEdge(Graph* myGraph, int myFromNodeID, int myToNodeID, double myEdgeweight){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null/empty graph, failed");
        exit(1);
    }

    // find the from node
    Node* currentNode = myGraph->head;
    while(currentNode->nodeID != myFromNodeID){
        currentNode = currentNode->nextNode;
    }
    if(currentNode == NULL){ // if the from node doesn't exist in the graph,exit the program
        deleteGraph(myGraph);
        exit(1);
    }

    // create a new edge
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->toNodeID = myToNodeID;
    newEdge->toNodeWeight = myEdgeweight;
    newEdge->NextEdge = NULL;
    
    // add the new edge to the end of the edge list
    Edge* currentEdge = currentNode->edgeInfo;
    while (currentEdge->NextEdge != NULL){
        currentEdge = currentEdge->NextEdge;
    }
    currentEdge->NextEdge = newEdge;

}

// free all the memory of a certain node
void freeCurrentNode(Node* currentNode){
    Edge* currentEdge = currentNode->edgeInfo;
    Edge* tempEdge ;
    while(currentEdge != NULL){ // free all the edge in that node
        tempEdge = currentEdge;
        currentEdge = currentEdge->NextEdge;
        free(tempEdge);
    }
    free(currentNode); // free the node itself
}


// check if an edge exist in the current node
int checkIfEdgeExist(Node* currentNode, int toNodeID){
    Edge* currentEdge = currentNode->edgeInfo->NextEdge;
    while(currentEdge != NULL){ // check each edge in the edge list
        if(currentEdge->toNodeID == toNodeID)
            return 1;
        currentEdge = currentEdge->NextEdge;
    }
    return 0;
}

// delete a certian node
void deleteNode(Graph* myGraph, int myNodeID){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null/empty graph, failed");
        exit(1);
    }

    Node* currentNode = myGraph->head->nextNode;
    Node* prevNode = myGraph->head;
    int nodeExist = 0; // set a variable to check if the from node exists in the graph
    while(currentNode != NULL){
        if(currentNode->nodeID == myNodeID){
            // the from node is found
            prevNode->nextNode = currentNode->nextNode;
            freeCurrentNode(currentNode);
            nodeExist = 1;
            currentNode = prevNode->nextNode;
        }else{ // delete all the edges with the input node as the to node
            if(checkIfEdgeExist(currentNode,myNodeID) == 1){ 
                nodeExist = 1;
                deleteEdge(myGraph,currentNode->nodeID,myNodeID);
            }
            prevNode = currentNode;
            currentNode = currentNode->nextNode;
        }
    }

    // if the node doesn't exist in the graph,exit the program
    if(nodeExist == 0){
        deleteGraph(myGraph);
        exit(1);
    }
    
}
    
// delete a given edge
void deleteEdge(Graph* myGraph, int myFromNodeID, int myToNodeID){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null graph, failed");
        exit(1);
    }

    Node* currentNode = myGraph->head->nextNode;

    // look for the from node of the edge
    while(currentNode != NULL && currentNode->nodeID != myFromNodeID){
        currentNode = currentNode->nextNode;
    }

    // if the from node is not found, delete the graph and exit
    if(currentNode == NULL){
        deleteGraph(myGraph);
        exit(1);
    }

    // look for the edge with the given to-node id
    Edge* currentEdge = currentNode->edgeInfo->NextEdge;
    Edge* prevEdge = currentNode->edgeInfo;
    while(currentEdge != NULL && currentEdge->toNodeID != myToNodeID){
        prevEdge = currentEdge;
        currentEdge = currentEdge->NextEdge;
    }
    // if the to-node doesn't exist in the edge list, delete the graph and exit
    if(currentEdge == NULL){
        deleteGraph(myGraph);
        exit(1);
    }
    
    prevEdge->NextEdge = currentEdge->NextEdge;  
    free(currentEdge);

}

//calculate the number of nodes in the graph
int calcNumNodes(Graph* myGraph){
    if(myGraph == NULL ){
        printf("null/empty graph, failed");
        return 0;
    }
    if(myGraph->head == NULL){
        return 0;
    }
    int count = 0;
    Node *currentNode = myGraph->head->nextNode;
    while(currentNode!= NULL){ // iterate through the node list
        count++;
        currentNode = currentNode->nextNode;
    }
    return count;
}

// calculate the number of edges in the graph
int calcNumEdges(Graph* myGraph){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null/empty graph, failed");
        return 0;
    }
    int totalEdgeCount = 0;
    Node *currentNode = myGraph->head->nextNode;
    while(currentNode != NULL){ // iterate through the node list
        Edge* currentEdge = currentNode->edgeInfo->NextEdge;
        while(currentEdge != NULL){ // iterate through the edge list
            totalEdgeCount++;
            currentEdge = currentEdge->NextEdge;
        }
        currentNode = currentNode ->nextNode;
    }

    return totalEdgeCount;

}

// print the node list
void printNodeList(Graph* myGraph){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null/empty graph, failed");
        return ;
    }

    Node *currentNode = myGraph->head->nextNode;
    while(currentNode != NULL){  // iterate through the node list
        if(currentNode->nextNode == NULL) printf("%d\n", currentNode->nodeID);
        else printf("%d ",currentNode->nodeID); // print the node id
        currentNode = currentNode->nextNode;
    }
    
}

// print the edge lists
void printEdgeList(Graph* myGraph){
    if(myGraph == NULL || myGraph->head == NULL){
        printf("null/empty graph, failed");
        return ;
    }

    Node *currentNode = myGraph->head->nextNode;
    while(currentNode != NULL){ // iterate through the node list
        Edge* currentEdge = currentNode->edgeInfo->NextEdge;
        while(currentEdge != NULL){ // iterate through the edge list
            printf("(%d, %d, %f)\n",currentNode->nodeID,currentEdge->toNodeID,currentEdge->toNodeWeight); // print the edge
            currentEdge = currentEdge->NextEdge;
        }
        currentNode = currentNode->nextNode;
    }
}