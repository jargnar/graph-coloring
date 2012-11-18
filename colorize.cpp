#include "graph.h"
#include "colorize.h"

int colors;
int Vcolor[100];
int possible[100][100];
int spilledV[100];
int spilledVsize=0;
int Psize;

void setColors(int colr) {
	colors = colr;
}

/* The possibility heuristic checks for possible colors
   that can be assigned to a vertex V
   based on its neighbors colors
   and keeps track of this intelligence in an array 'possible[]'
*/
void buildPossibility(int pos) {
	Psize = colors;	
	for(int i=0; i<colors; ++i) {
		possible[pos][i]=i;
	}
}

void removePossibility(int pos, int colr) {
	int Index = -1;
	for(int i=0; i<Psize; ++i) {
		if(possible[pos][i]==colr) Index = i;	
	}
	if(Index!=-1) {
		for(int i=Index; i<Psize-1; ++i) {
			possible[pos][i] = possible[pos][i+1];
		}
		Psize = Psize - 1;
	}
}

int getColor(int pos) {
	return Vcolor[pos];
}

/* Those variables which need to be stored in the mem */
void spill(int pos) {
	spilledV[spilledVsize] = V[pos];
	eraseVertex(pos);
	eraseEdge(pos);
	for(int i=0; i<Vsize; ++i) {
		for(int j=0; j<Esize[i]; ++j) {
			if(spilledV[spilledVsize]==E[i][j]) {
			eraseSingleEdge(i,j);			
			break;
			}
		}		
	}
	spilledVsize = spilledVsize + 1;
}

/* Reduces interference Graph */
void simplify() {
	int tmp = Vsize;
	bool SpillCondition = true;	
	for(int i=0; i<tmp; ++i) {
		if(Vsize==1) break;
		for(int j=0; j<Vsize; ++j) {
			if(Esize[j]<colors) SpillCondition = false; 
		}
		if(SpillCondition) {
			spill(i);
			i=0;
			continue;		
		}
		if(Esize[i]<colors) {
			printGraph();
			deleteVertex(V[i]);
			i=0;
		}
	}
}

/* Greedily Selects Colors */
void select(int pos) {
	
	
	buildPossibility(pos);	
	
	if((Vsize == 1)&&(V[0]==V[pos])&&(getIndex(V[pos])==0)) { 
		Vcolor[0] = possible[pos][0];
		return;	
	}

	int Vpos = getIndex(V[pos]);
	
	/*Traverse thru all edges of Vertex v,
	  which we are about to color,
	  to eliminate the colors which are already taken
          using the possibility heuristic	
	*/

	int tmpV;
	for(int i=0; i<Esize[Vpos]; ++i) {
		tmpV = E[Vpos][i];
		removePossibility(Vpos,getColor(getIndex(tmpV)));
	}
	
	Vcolor[getIndex(V[pos])] = possible[pos][0];
}
		
		
		
		
