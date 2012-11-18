#ifndef GRAPH_H
#define GRAPH_H

extern int V[100];
extern int E[100][100];

extern int Vsize;
extern int Esize[100];

extern int stackV[100];
extern int stackE[100][100];
extern int stackEsize[100];

extern int stackPtr;

extern void printGraph();
extern void insertVertex(int, int, int []);
extern void deleteVertex(int);
extern int getIndex(int);
extern void pop();
extern void eraseVertex(int);
extern void eraseEdge(int);
extern void eraseSingleEdge(int,int);

#endif
