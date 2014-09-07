#ifndef __SVM__IO__
#define __SVM__IO__
#include "graph.h"
#include "Set.h"
#include "vectorarray.h"
#include <string.h>
#include "equation.h"

#define PLUS1 1
#define MINUS1 -1
class svmio{
private:
	double infinity;
	equation Equation;

	void addEquations(graph &g,const int queryIndex,const int u,const int v);
	void addDummyEquation(graph &g,const int queryIndex,const int u);
	void addEquation(graph &g,const int u,const int v,vectorarray interSectionVector,int flag,Set VertexSet,int entryIndex);
	vectorarray computeIntersectionPart(graph &g,int u,int v,Set SampledNeighborsofU,Set SampledNeighborsofV);
public:
	svmio();
	void setOutputFile(const char *filename);
	void setInfinity(double inf);
	void convertGraphAndQueryToSVMLITE(graph &g,Set &Query);
};
#endif