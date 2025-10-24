#include <stdio.h>
#define NODES 20

void main(int argc, char *argv[]) 
{

	// read the elements of the adjacency matrix from the file
	FILE *fp; 
	fp = fopen("testgraph4x5.txt","r");	
	int i, j, temp0;
	for(i=0; i<NODES; i++)
		for (j=0; j<NODES; j++)
		{
			fscanf(fp,"%d", &temp0);
			// print statement for verification only; remove or comment out
			printf("i = %d, j= %d, value = %d\n",i,j,temp0);
		}
	fclose(fp);
			
}

