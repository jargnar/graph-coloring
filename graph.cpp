#include <iostream>
#include "graph.h"
#include "colorize.h"

using namespace std;

/* Note that the following graph structure is already declared in graph.h
   as extern variables.
   These are definitions.
*/

int V[100];
int E[100][100];

int Vsize=0;
int Esize[100];

int stackV[100];
int stackE[100][100];

int stackPtr = 0;
int stackEsize[100];

/* End of Global datastructures that are declared in graph.h */


void eraseVertex(int index) {
	for(int i=index; i<Vsize-1; ++i) {		
		V[i] = V[i+1];	
	}
	Vsize = Vsize - 1;
}

void eraseEdge(int index) {

	/* Should logically by i=index to Vsize-1 but global Vsize already altered above. 
	   This is a cheap trick. :)	
	*/
	for(int i=index; i<Vsize; ++i) {
		for(int j=0; j<Esize[i+1]; ++j) {
			E[i][j] = E[i+1][j];
		}
		Esize[i] = Esize[i+1];
	}
}

void eraseSingleEdge(int index, int jndex) {
	for(int i=jndex; i<Esize[index]-1; ++i) {
		E[index][i] = E[index][i+1];	
	} 
	Esize[index] = Esize[index] - 1;
}

/* Checks if an Element ele exists in an Array arr[] whose size is asize */
bool exists(int ele, int asize, int arr[]) {
	int i;
	for(i=0; i<asize; ++i) {
		if(arr[i] == ele) return 1;
	}
	return 0;
}

/* Pops the top G(v,e) set from stack to graph */
void pop() {
	int tos = stackPtr - 1;
	int v = stackV[tos];
	int esize = stackEsize[tos];
	int e[esize];
	for(int i=0; i<esize; ++i) {
		e[i] = stackE[tos][i];	
	}
	insertVertex(v,esize,e);
	stackPtr = stackPtr - 1;
}
	

/* Returns the position of a vertex v in the V[] data struct */
int getIndex(int v) {
	int Index = -1;
	for(int i = 0; i < Vsize; ++i) {
		if(v==V[i]) Index = i;
	}
	return Index;
}


/*Inserts a Vertex v into V[], and its edges e[] into E[][]*/
void insertVertex(int v, int esize, int e[]) {
	int i, currV;
	if(Vsize == 0) {
		Vsize = 1;
		V[0] = v;
		for(i=0; i<esize; ++i) {
			E[0][i] = e[i];
		}
		Esize[0] = esize;
	} 
	else {
		currV = Vsize;
		Vsize = Vsize + 1;
		V[currV] = v;
		for(i=0; i<esize; ++i) {
			E[currV][i] = e[i];
		}
		Esize[currV] = esize;
		for(i=0; i<Vsize; ++i) {
			if((!(exists(v,Esize[i],E[i])))&&(exists(V[i],esize,e)))
			{
				E[i][Esize[i]] = v;
				Esize[i] = Esize[i] + 1;
			}
		}
	}
	//printGraph();
}	

/*Deletes a vertex with value v*/
void deleteVertex(int v) {
	int DeletionIndex = -1;
	for(int i = 0; i < Vsize; ++i) {
		if(v==V[i]) DeletionIndex = i;
	}
	if(DeletionIndex == -1) cout<<"\nVERTEX NOT FOUND\n";
	else {
		/*Saves onto the Stack before proceding */

		stackV[stackPtr] = V[DeletionIndex];
		stackEsize[stackPtr] = Esize[DeletionIndex];
		for(int i=0; i<Esize[DeletionIndex]; ++i)
			stackE[stackPtr][i] = E[DeletionIndex][i];
		stackPtr = stackPtr + 1;

		/* erases V[DeletionIndex] */
		eraseVertex(DeletionIndex);

		/* erases E[DeletionIndex][] */
		eraseEdge(DeletionIndex);

		
		/* Any v occurence in the Edges of other Vertices?
	           Checks and deletes */
		for(int i=0; i<Vsize; ++i) {
			for(int j=0; j<Esize[i]; ++j) {

				if(v==E[i][j]) {
				eraseSingleEdge(i,j);			
				break;
				}
			}		
		}
	}
}

/*Prints the Interference Graph*/
void printGraph() {
	int i, j;
	cout<<"\nVERTEX \tEDGES \tCOLOR";
	for(i=0; i<Vsize; ++i) {
		cout<<"\n"<<V[i]<<"\t";
		for(j=0; j<Esize[i]; ++j) {
			cout<<E[i][j];
		}
		cout<<"\t"<<Vcolor[i];
	}
	cout<<"\n";
}
