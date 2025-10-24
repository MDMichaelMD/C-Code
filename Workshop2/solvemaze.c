//create read record steps bfs
#include <stdio.h>
#include <stdlib.h>
//use fix size to avoid extra work
#define ROWS 4 //define the number of rows
#define COLS 5 //define the number of columns
#define NODES ROWS*COLS //creates a 4 by 5
// Create a structure to define the queue
typedef struct
{
    int queue[NODES]; // Array to hold queue elements 
    int front; // Index of the front element
    int rear;  // Index of the next empty spot at the rear
} Queue;

// Function to add an element to the queue
void enqueue(Queue *q, int value) 
{
    q->queue[q->rear++] = value; // Add new values at rear, then increment rear
}

// Function to remove and return an element from the queue
int dequeue(Queue *q)
{
    return q->queue[q->front++]; // Return value at front, then increment front
}

// Function to check if the queue is empty
int is_empty(Queue *q)
{
    return q->front == q->rear; // Queue is empty if front and rear are equal
}

// function to perform Breadth-First Search (BFS) on the graph
void bfs(int start, int finish, int adjm[NODES][NODES]) 
{
    //define variables
    int vis[NODES] = {0}; // Array to track visited nodes, starts at 0
    int pre[NODES];   // Array to store the predecessor of each node
    Queue q = { .front = 0, .rear = 0 }; // Initialize queue with front and rear at 0
    
    // Start BFS by enqueueing the start node
    enqueue(&q, start);
    vis[start] = 1;       // Mark the start node as visited
    pre[start] = -1;  // Start node has no predecessor

    // BFS loop to explore all reachable nodes
    while (!is_empty(&q)) //The while loop continues until the queue is empty.
    {
        int current = dequeue(&q); // Dequeue the next node to process

        // If the finish node is found, exit the loop
        if (current == finish) 
        {
            break; //break from loop
        }

        // Explore all neighbors of the current node
        for (int i = 0; i < NODES; i++) // for loop to explorer neighbors
        {
            if (adjm[current][i] == 1 && !vis[i]) //check if there is surrounding unexplored
             {
                enqueue(&q, i);  // Enqueue the neighbor
                vis[i] = 1;  // Mark the neighbor as visited
                pre[i] = current; // Record the predecessor of node i
            }
        }
    }

    // Reconstruct the path from finish to start using the predecessor array
    int path[NODES]; // Array to store the path
    int path_ind = 0; // Index to track the path array
    for (int at = finish; at != -1; at = pre[at]) 
    {
        path[path_ind++] = at; // Add each node to the path
    }

    // Print the path from start to finish by reversing the path
    for (int i = path_ind - 1; i >= 0; i--) 
    {
        if (i == 0)  printf("%d\n", path[i]); // Print each node in the path and at end do not print extra space
        
        else printf("%d ", path[i]); // Print each node in the path
    }
   
}

// Main function to drive the program
int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 3)
    {
        return 1; // Exit if incorrect arguments
    }

    // Convert commandline arguments to integers
    int start = atoi(argv[1]); //note additional library
    int finish = atoi(argv[2]);
    int adjm[NODES][NODES]; // Define the adjacency matrix to hold the graph

    // Open the file containing the adjacency matrix
    FILE *file = fopen("testgraph4x5.txt", "r");
    if (file == NULL) 
    {
            return 1; // Exit if error
    }

    // Read the adjacency matrix from the file from i to i then j to j (nesteded)
    for (int i = 0; i < NODES; i++) 
    {
        for (int j = 0; j < NODES; j++) 
        {
            fscanf(file, "%d", &adjm[i][j]); // Read each value into the matrix
        }
    }

    fclose(file); // Close the file once done
    bfs(start, finish, adjm);// heart of reading" use bfs to read/find the path from start to finish on the adjmatrix

    return 0; // Exit successfully
}
