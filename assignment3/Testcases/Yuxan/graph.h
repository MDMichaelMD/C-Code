// header file: structs and function declarations for graphs


typedef struct edge Edge;

typedef struct node Node;

typedef struct graph Graph;




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

// add any additional function declarations