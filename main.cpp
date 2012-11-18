#include <iostream>
#include "graph.h"
#include "colorize.h"

using namespace std;

int main() {
	int i, n, colr, v, e[100], esize;
	cout<<"No of Colors(Registers): ";
	cin>>colr;
	setColors(colr);
	cout<<"No of Vertices: ";
	cin>>n;
	int ntmp = n;
	while(ntmp--) {
		cout<<"\nVertex: ";
		cin>>v;
		cout<<"\nNo of Edges: ";
		cin>>esize;
		cout<<"\nEdges: ";
		for(i=0; i<esize; ++i) cin>>e[i];
		insertVertex(v,esize,e);		
	}
	
	printGraph();
	cout<<"\n\n SIMPLIFYING\n\n";
	simplify(); 
	
	for(int j=0; j<Vsize; ++j)
	 {
		if(stackPtr+1) {
		cout<<"\n\n SELECTING ("<<j+1<<")\n";
		select(j);
		printGraph();
		pop();
		}
	}

	if(spilledVsize>0) {
		cout<<"\n SPILLED VARIABLES: \n";
		for(int k=0; k<spilledVsize; k++) {
			cout<<spilledV[k]<<"\n";
		}
	}
	
	cout<<"\n";
	return 0;
}
