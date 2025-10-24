#ifndef MODEL_H
#define MODEL_H
typedef struct node {
	double v;
	double cai;
	double casr;
	double m;
	double h;
	double j;
	double d;
	double f;
	double fca;
	double kr;
	double ks;
	double xto;
	double yto;
} Node;

void initializeNode(Node* mynode);
void updateNode(Node* mynode, Node* mynodenew, double diffusionValue);
#endif
