#ifndef __ADJACENCY_GRAPH__
#define __ADJACENCY_GRAPH__
#include <stdio.h>
#include <stdlib.h>
#include <set>

class adjacencygraph{
private:
	std::vector<std::set> adjacencyList;
public:
	adjacencygraph(int n);
	void addEdge(int i,int j);
	bool isExist(int i,int j);
	
};


#endif