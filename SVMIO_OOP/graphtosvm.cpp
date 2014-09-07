#include "graph.h"
#include "Set.h"
#include "vectorarray.h"
#include "svmio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "other.h"

#include "config.h"

// #define ADJACENCYFILE "netflix_adjacency.txt"
// #define FEATUREFILE "netflix_feature.txt"
// #define QUERYFILE "netflix_query.txt"
// #define N 17770
// #define F 64

//#define ADJACENCYFILE "movielens_adjacency.txt"
//#define FEATUREFILE "movielens_feature.txt"
//#define QUERYFILE "movielens_query.txt"
//#define N 3952
//#define F 18


// #define ADJACENCYFILE "test_adjacency.txt"
// #define FEATUREFILE "test_feature.txt"
// #define QUERYFILE "test_query.txt"
// #define N 1000
// #define F 18



//#define OUTPUTFILE "output.txt"
//#define EDGEPERCENTAGE 1
//#define NONEDGEPERCENTAGE 1


int main(){
	Clock Tclock;
	Tclock.start();
	Set Query(QUERYFILE);
	//int temp;
	graph G(N,F,ADJACENCYFILE,FEATUREFILE);
	
	printf("\nGraph Loaded !!\n");
	//scanf("%d",&temp);

	G.sampleGraph(EDGEPERCENTAGE,NONEDGEPERCENTAGE);

	printf("\nGraph Sampled !!\n");
	//scanf("%d",&temp);

	svmio SVMIOCREATOR;
	FILE *f = fopen(OUTPUTFILE,"w");
	fclose(f);
	SVMIOCREATOR.setOutputFile(OUTPUTFILE);
	SVMIOCREATOR.setInfinity(30);

	SVMIOCREATOR.convertGraphAndQueryToSVMLITE(G,Query);

	Tclock.show();
	return 0;
}
