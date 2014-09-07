#include "graph.h"
#include "vectorarray.h"
#include "Set.h"
#include <stdio.h>
#include <stdlib.h>
#include "other.h"
#include <vector>

#define ADJACENCYFILE "test_adjacency.txt"
#define FEATUREFILE "test_feature.txt"
#define QUERYFILE "test_query.txt"


#define N 1000
#define F 18
#define QUERYSIZE 30

#define EDGEPERCENTAGE 0.5
#define NONEDGEPERCENTAGE 0.5

void generateRandomeAdjacency(int n,const char *filename){
	FILE *f = fopen(filename,"w");
	int adj[n][n];
	for(int i=0;i<n;i++){
		loadBar(i,n,50,50);
		for(int j=0;j<i;j++){
			int con = rand()%4;
			if(con == 0){
				adj[i][j] = 0;
				adj[j][i] = 0;
			}else{
				adj[i][j] = 1;
				adj[j][i] = 1;
			}
		}
		adj[i][i] = 0;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fprintf(f," %d ",adj[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
	return;
}

void generateFeatureFile(int n,int fSize,const char *filename){
	int feature[n][fSize];
	for(int i=0;i<n;i++){
		loadBar(i,n,50,50);
		for(int j=0;j<fSize;j++){
			feature[i][j] = rand()%10;
		}
	}
	FILE *f = fopen(filename,"w");

	for(int j=0;j<fSize;j++){
		for(int i=0;i<n;i++){
			fprintf(f, " %d ", feature[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
	return;
}

void testGetFeature(graph &G){

	vectorarray FDiff = G.getEdgeFeature(0,9);
	FDiff.print();

	vectorarray FDiff1 = G.getEdgeFeature(1,2);
	FDiff1.print();

	vectorarray FDiff2 = G.getEdgeFeature(1,1);
	FDiff2.print();

	return;
}

void testGetNeighborsAndSampling(graph &G){
	Set neighbor[G.getNodeCount()];
	Set nonNeighbor[G.getNodeCount()];
	Set sampledNeighbor[G.getNodeCount()];
	Set sampledNonNeighbor[G.getNodeCount()];

	G.sampleGraph(EDGEPERCENTAGE,NONEDGEPERCENTAGE);

	for(int i=0;i<G.getNodeCount();i++){
		neighbor[i] = G.getNeighbors(i);
		nonNeighbor[i] = G.getNonNeighbors(i);
		Set sampledNeighbor = G.getSampledNeighbors(i);
		Set sampledNonNeighbor = G.getSampledNonNeighbors(i);
		sampledNeighbor.sort();
		sampledNonNeighbor.sort();
		printf("\nFor Node = %d",i);
		neighbor[i].print();
		sampledNeighbor.print();
		nonNeighbor[i].print();
		sampledNonNeighbor.print();
		// (nonNeighbor[i]+neighbor[i]).print();
	}
	return;
}
void generateQueryFile(int n,int k,const char *filename){
	std::vector<int> nodeList;
	nodeList.resize(n);
	for(int i=0;i<n;i++){
		nodeList[i] = i;
	}
	std::vector<int> Query = selectKItems(nodeList,n,k);

	FILE *f = fopen(filename,"w");
	for(int i=0;i<Query.size();i++){
		loadBar(i,n,50,50);
		fprintf(f, "%d ",Query[i]);
	}
	fprintf(f, "-1");
	fclose(f);
	return;
}
int main(){

	generateRandomeAdjacency(N,ADJACENCYFILE);
	generateFeatureFile(N,F,FEATUREFILE);
	generateQueryFile(N,QUERYSIZE,QUERYFILE);
	// graph G(N,F,ADJACENCYFILE,FEATUREFILE);

	// printf("\nNode Size = %d Feature DIM = %d\n",G.getNodeCount(),G.getFSize());

	// G.printAdjacency(); // working
	// G.printFeature(); // working

	// testGetFeature(G);
	// testGetNeighborsAndSampling(G);
	return 0;
}