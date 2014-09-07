#include "svmio.h"
#include "other.h"
#include "config.h"


svmio::svmio(){
	infinity = 30;
	return;
}
void svmio::setOutputFile(const char *filename){
	// printf("\nIN SVMIO : output file {%s}\n",filename);
	Equation.setOutputFileName(filename);
	return;
}
void svmio::convertGraphAndQueryToSVMLITE(graph &g,Set &Query){
	for(int i=0;i<Query.getSize();i++){
		loadBar(i,Query.getSize(),50,50);
		//printf("\nAdding For %d\n",Query.getElement(i));
		for(int j=0;j<g.getNodeCount();j++){
			svmio::addEquations(g,i,Query.getElement(i)-1,j);
		}
	}
	return;
}
void svmio::addEquations(graph &g,const int queryIndex,const int u,const int v){
	if(u == v){
		svmio::addDummyEquation(g,queryIndex,u);
		return;
	}
	// Set SampledNeighborosfU = g.getSampledNeighbors(u);
	// Set SampledNeighborsofV = g.getSampledNeighbors(v);
	// Set SampledNonNeighborsofU = g.getSampledNonNeighbors(u);
	// Set SampledNonNeighborsofV = g.getSampledNonNeighbors(v);

	Set& SampledNeighborosfU = g.sampledNeighbor[u];
	Set& SampledNeighborsofV = g.sampledNeighbor[v];
	Set& SampledNonNeighborsofU = g.sampledNonNeighbor[u];
	Set& SampledNonNeighborsofV = g.sampledNonNeighbor[v];

	vectorarray interSectionVector = svmio::computeIntersectionPart(g,u,v,SampledNeighborosfU,SampledNeighborsofV);
	
	// int index = (u * g.getNodeCount() + v) * g.getFSize();
	// int index = (queryIndex * g.getNodeCount() + v) * g.getFSize();
	int index = (queryIndex * g.getNodeCount() + v) * g.getFSize() + 1; // for liblinear

	// printf("\nAdding FOR {%d,%d}",u,v);

	svmio::addEquation(g,u,v,interSectionVector,MINUS1,SampledNeighborosfU * SampledNonNeighborsofV,index);
	svmio::addEquation(g,v,u,interSectionVector,MINUS1,SampledNeighborsofV * SampledNonNeighborsofU,index);
	svmio::addEquation(g,u,v,interSectionVector,PLUS1,SampledNeighborsofV * SampledNonNeighborsofU,index);
	svmio::addEquation(g,v,u,interSectionVector,PLUS1,SampledNeighborosfU * SampledNonNeighborsofV,index);

	return;
}
void svmio::addDummyEquation(graph &g,const int queryIndex,const int u){
	// int index = (u*g.getNodeCount()+u)*g.getFSize();
	// int index = (queryIndex * g.getNodeCount() + u) * g.getFSize();
	int index = (queryIndex * g.getNodeCount() + u) * g.getFSize() + 1; // for  liblinear
	Equation.reset(-1);
	for(int i=0;i<g.getFSize();i++){
		Equation.add(index+i,infinity);
	}
	Equation.addToFile();
	Equation.addToFile();

	Equation.reset(1);
	for(int i=0;i<g.getFSize();i++){
		Equation.add(index+i,infinity);
	}
	Equation.addToFile();
	Equation.addToFile();
	return;
}
void svmio::addEquation(graph &g,const int u,const int v,vectorarray interSectionVector,int flag,Set VertexSet,int entryIndex){
	
	// VertexSet.print();

	Equation.reset(flag);
	int n = g.getNodeCount();
	int fSize = g.getFSize();

	vectorarray sumDiff(fSize);
	sumDiff.set(0);



	// Set VertexSet = SampledNeighborosfU * SampledNonNeighborsofV;

	vectorarray edgeFeature(fSize);
	for(int i=0;i<VertexSet.getSize();i++){
		edgeFeature = g.getEdgeFeature(u,VertexSet.getElement(i));
		sumDiff = sumDiff + edgeFeature;
	}
	if(VertexSet.getSize() > 0){
		// printf("found !!\n");
		sumDiff = sumDiff / VertexSet.getSize();
	}
	sumDiff = sumDiff - interSectionVector;

	// int entryIndex = (u*n + v) * fSize;
	for(int i=0;i<fSize;i++){
		Equation.add(entryIndex+i,sumDiff.get(i));
	}
	//Equation.print();
	Equation.addToFile();
	return;
}
vectorarray svmio::computeIntersectionPart(graph &g,int u,int v,Set SampledNeighborsofU,Set SampledNeighborsofV){
	int fSize = g.getFSize();
	vectorarray interSectionVector(fSize);

	if(INTERSECTIONPART == USESB){
		interSectionVector = g.getEdgeFeature(u,v);
		return interSectionVector;	
	}
	
	Set SampledIntersection = SampledNeighborsofU * SampledNeighborsofV;
	

	int intersectionSize = SampledIntersection.getSize();
	if(intersectionSize == 0){
		interSectionVector.set(infinity);
	}else{
		vectorarray sumIntersect(fSize),edgeFeature_withU(fSize),edgeFeature_withV(fSize);
		sumIntersect.set(0);
		for(int i=0;i<intersectionSize;i++){
			edgeFeature_withU = g.getEdgeFeature(u,SampledIntersection.getElement(i));
			edgeFeature_withV = g.getEdgeFeature(v,SampledIntersection.getElement(i));
			
			sumIntersect = sumIntersect + (edgeFeature_withU + edgeFeature_withV) / 2;
		}
		interSectionVector = sumIntersect/intersectionSize;
	}
	return interSectionVector;
}
void svmio::setInfinity(double inf){
	infinity = inf;
	return;
}