#ifndef BOOSTBASEDGRAPH
#define BOOSTBASEDGRAPH

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Set.h"
#include "vectorarray.h"
/*************** BOOST LIBRARY FOR CREATING LARGE GRAPHS *************/
// Boost
#include <boost/graph/undirected_graph.hpp>// A subclass to provide reasonable arguments to adjacency_list for a typical undirected graph
#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_iterator.hpp>
typedef boost::undirected_graph<> Graph;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
/*********************************************************************/

class graph{
private:
	Graph g;
	int n;
	int fSize;
	std::vector<Graph::vertex_descriptor> v;
	std::vector<vectorarray> nodeFeatures;
	void createGraphFromAdjacencyMatrix(int n,const char *filename); // tested
	void getNodeFeaturesFromFile(int n,int fSize,const char *filename); // tested
	void initNodeFeaturesMatrix(int n,int fSize); // tested
	void initMatrices(int n,int fSize); // tested
	void sample(int q,double edgePrecentage,double nonEdgePercentage); // tested
public:
	std::vector<Set> sampledNeighbor;
	std::vector<Set> sampledNonNeighbor;

	
	graph(int n,int fSize,const char *adjacencyFile,const char *featureFile);
	void sampleGraph(const double edgePrecentage,const double nonEdgePercentage);
	void sampleGraph(Set querySet,double edgePrecentage,double nonEdgePercentage); // tested
	Set getSampledNonNeighbors(const int i); // tested
	Set getSampledNeighbors(const int i); // tested
	vectorarray getEdgeFeature(const int i,const int j); // tested
	bool isExist(const int i,const int j); //tested
	Set getNeighbors(const int u); // tested
	Set getNonNeighbors(const int u); // tested
	int getNodeCount(); // tested
	int getFSize(); // tested

	/************ debug functions ********************/
	void printAdjacency();
	void printFeature();
};
#endif