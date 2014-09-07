#include "graph.h"
#include "other.h"
#include <math.h>

graph::graph(int n,int fSize,const char *adjacencyFile,const char *featureFile){
	this->n = n;
	this->fSize = fSize;
	graph::initMatrices(n,fSize);
	graph::createGraphFromAdjacencyMatrix(n,adjacencyFile);
	graph::getNodeFeaturesFromFile(n,fSize,featureFile);
	return;
}
void graph::createGraphFromAdjacencyMatrix(int n,const char *filename){
	FILE *f = fopen(filename,"r");
	if(f == NULL){
		printf("\nADJACENCY MATRIX FILE CAN NOT FOUND !!\n");
		exit(-1);
	}
	for(int i=0;i<n;i++){
		v[i] = g.add_vertex();
	}
	int value;
	for(int i = 0;i<n;i++){
		loadBar(i,n,50,50);
		//printf("\nAdding node = %d\n",i);
		for(int j=0;j<n;j++){
			int fscnafreturn = fscanf(f,"%d",&value);
			if(value == 1){
				// edge exist between v[i] and v[j]
				if(!(boost::edge(v[i], v[j], g).second)){
					// printf("\nADDING :{%d - %d}",i,j);
					g.add_edge(v[i],v[j]);
				}
			}
		}
	}
	fclose(f);
	return;
}
void graph::getNodeFeaturesFromFile(int n,int fSize,const char *filename){
	FILE *f = fopen(filename,"r");
	if(f == NULL){
		printf("\nERROR : NODE FEATURE FILE NOT FOUND !!");
		exit(-1);
	}
	double value;
	for(int i = 0;i<fSize;i++){
		for(int j = 0 ;j<n;j++){
			int fscnafreturn = fscanf(f,"%lf",&value);
			nodeFeatures[j].set(i,value);
		}
	}
	return;
}
void graph::initNodeFeaturesMatrix(int n,int fSize){
	nodeFeatures.clear();
	nodeFeatures.resize(n);
	for(int i=0;i<n;i++){
		vectorarray vec = vectorarray(fSize);
		nodeFeatures[i] = vec;
	}
	return;
}
void graph::initMatrices(int n,int fSize){
	graph::initNodeFeaturesMatrix(n,fSize);

	sampledNonNeighbor.clear();
	sampledNeighbor.clear();
	v.clear();

	v.resize(n);
	sampledNeighbor.resize(n);
	sampledNonNeighbor.resize(n);
	return;
}
void graph::sample(int q,double edgePrecentage,double nonEdgePercentage){
	// Set Neighbors = graph::getNeighbors(q);
	// sampledNeighbor[q] = Neighbors.SetToVector();
	// sampledNeighbor[q].reduceSizeInPlace(edgePrecentage);
	// Set nonNeighbors = graph::getNonNeighbors(q);
	// sampledNonNeighbor[q] = nonNeighbors.SetToVector();
	// sampledNonNeighbor[q].reduceSizeInPlace(nonEdgePercentage);


	sampledNeighbor[q] = graph::getNeighbors(q);
	sampledNeighbor[q].reduceSizeInPlace(edgePrecentage);
	sampledNonNeighbor[q] = graph::getNonNeighbors(q);
	sampledNonNeighbor[q].reduceSizeInPlace(nonEdgePercentage);

	return;
}
void graph::sampleGraph(const double edgePrecentage,const double nonEdgePercentage){
	for(int i=0;i<n;i++){
		loadBar(i,n,50,50);
		graph::sample(i,edgePrecentage,nonEdgePercentage);
	}
	return;
}
void graph::sampleGraph(Set querySet,double edgePrecentage,double nonEdgePercentage){
	int querySize = querySet.getSize();
	for(int i=0;i<querySize;i++){
		sample(querySet.getElement(i),edgePrecentage,nonEdgePercentage);
	}
	return;
}
Set graph::getSampledNonNeighbors(const int i){
	if(i<0 || i>= n){
		printf("\nError Non enough node !!\n");
		exit(-1);
	}
	return Set(sampledNonNeighbor[i]);
}
Set graph::getSampledNeighbors(const int i){
	if(i<0 || i>= n){
		printf("\nError Non enough node !!\n");
		exit(-1);
	}
	return Set(sampledNeighbor[i]);
}
vectorarray graph::getEdgeFeature(const int i,const int j){
	if(i>=n||j>=n||i<0||j<0){
        printf("\nERROR EXIT\n");
        exit(-1);
    }
    vectorarray diff(fSize);
    diff = nodeFeatures[i] - nodeFeatures[j];
    for(int i=0;i<fSize;i++){
    	diff.set(i,fabs(diff.get(i)));
    }
    return diff;
}
bool graph::isExist(const int i,const int j){
	if((i>=n||j>=n||i<0||j<0)){
		printf("\nERROR EXIT\n");
		exit(-1);
	}
	return boost::edge(v[i], v[j], g).second;
}
Set graph::getNeighbors(const int u){
	Set neighbors;
	if(u<0||u>=n){
		printf("\nERROR EXIT\n");
		exit(-1);
	}
	for(int i=0;i<n;i++){
		if(graph::isExist(i,u)){
			neighbors.add(i);
		}
	}
    return neighbors;
}
Set graph::getNonNeighbors(const int u){
	Set nonNeighbors;
	if(u<0||u>=n){
		printf("\nERROR EXIT\n");
		exit(-1);
	}
	for(int i=0;i<n;i++){
		if(!graph::isExist(i,u)){
			nonNeighbors.add(i);
		}
	}
    return nonNeighbors;
}
int graph::getNodeCount(){
	return n;
}
int graph::getFSize(){
	return fSize;
}
/************ debug functions ********************/
void graph::printAdjacency(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(graph::isExist(i,j)){
				printf(" 1 ");
			}else{
				printf(" 0 ");
			}
		}
		printf("\n");
	}
	return;
}
void graph::printFeature(){
	for(int j=0;j<fSize;j++){
		for(int i=0;i<n;i++){
			printf(" %lf ",nodeFeatures[i].get(j));
		}
		printf("\n");
	}
	return;
}