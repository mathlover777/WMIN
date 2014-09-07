#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "Set.h"
#include "config.h"
#include "fileio.h"
#include "math.h"
#include "vectorarray.h"

struct edgerank{
	int id;
	double score;
};
// void addToQueryAdjacency(const char *queryadjanceny,int query,const char *adjacencyline){

// }


std::vector<vectorarray> nodeFeatures;
void getNodeFeaturesFromFile(int n,int fSize,const char *filename){
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
void initNodeFeaturesMatrix(int n,int fSize){
	nodeFeatures.clear();
	nodeFeatures.resize(n);
	for(int i=0;i<n;i++){
		vectorarray vec = vectorarray(fSize);
		nodeFeatures[i] = vec;
	}
	return;
}

vectorarray getEdgeFeature(const int i,const int j){
	// if(i>=n||j>=n||i<0||j<0){
 //        printf("\nERROR EXIT\n");
 //        exit(-1);
 //    }
    vectorarray diff(nodeFeatures[i].getSize());
    diff = nodeFeatures[i] - nodeFeatures[j];
    for(int i=0;i<diff.getSize();i++){
    	diff.set(i,fabs(diff.get(i)));
    }
    return diff;
}
bool isQuery(Set Query,int id){
	for(int i=0;i<Query.getSize();i++){
		if(Query.getElement(i) == id){
			return true;
		}
	}
	return false;
}
void extractQueryAdjacency(Set Query,const char *adjacencyfile,const char *queryadjanceny,int nodeCount){
	// Query.sort();
	// Query.print();
	// std::vector<int> queryList = Query.SetToVector();
	// printf("\n{");
	// for(int i=0;i<queryList.size();i++){
	// 	printf(" %d ",queryList[i]);
	// }
	// printf("}\n");
	FILE *f = fopen(adjacencyfile,"r");
	FILE *q = fopen(queryadjanceny,"w");
	// fclose(q);
	char buffer[400000];
	int qIndex = 0;
	for(int i=0;i<nodeCount;i++){
		// fscanf(f,"%[^\n]s",buffer);
		fgets(buffer,400000,f);
		clearTabs(buffer);
		if(isQuery(Query,i)){
			// printf("%s\n",buffer );
			fprintf(q, "%d %s\n",i,buffer);	
			qIndex++;
		}
	}
	fclose(f);
	fclose(q);
	return;
}
void getWLiblinear(FILE *f,double *W,int k){
	for(int i=0;i<k;i++){
		fscanf(f,"%lf",W+i);
	}
	return;
}
vectorarray extractW(double *W,int fSize,int i){
	vectorarray v(fSize);
	int startIndex = i * fSize;
	int j = 0;
	for(int k=startIndex;k<startIndex+fSize;k++){
		v.set(j,W[k]);
		j++;
	}
	return v;
}
int compare(edgerank a,edgerank b){
	return a.score < b.score ?1:0;
}
void saveToRankFile(const char *rankfile,int query,edgerank *edgeList,int n){
	FILE *rank = fopen(rankfile,"a");
	fprintf(rank, "%d ",query);
	for(int i=0;i<n;i++){
		fprintf(rank, " %d",edgeList[i].id );
	}
	fprintf(rank, "\n");
	fclose(rank);
	return;
}
void rank_Liblinear(const char *modelfile,const char *queryadjanceny,const char *rankfile,Set Query,int fSize,int n,int skipline){
	FILE *model = fopen(modelfile,"r");
	FILE *rank = fopen(rankfile,"w");
	Query.sort();
	fclose(rank);
	char line[1000];
	for(int i=0;i<skipline;i++){
		// fscanf(model,"%[^\n]s",line);
		fgets(line,1000,model);
		clearTabs(line);
		// printf("%s\n",line);
	}
	double *W = (double *)malloc(sizeof(double) * (n*fSize));
	for(int i=0;i<Query.getSize();i++){
		edgerank edgeList[n];
		getWLiblinear(model,W,n*fSize);
		for(int j=0;j<n;j++){
			vectorarray w_ij = extractW(W,fSize,j);
			// w_ij.print();
			edgeList[j].id = j;
			edgeList[j].score = w_ij * getEdgeFeature(Query.getElement(i),j);
		}
		std::sort(edgeList,edgeList+n, compare);
		saveToRankFile(rankfile,Query.getElement(i),edgeList,n);
	}
	fclose(model);
	return;
}
void getAdjacencyVector(int query,bool *adjacencyvector,int n,FILE *f){
	for(int i=0;i<n;i++){
		adjacencyvector[i] = false;
	}
	int queryfromfile;
	fscanf(f,"%d",&queryfromfile);
	if(queryfromfile != query){ // its just a cross check for consistency
		printf("ERROR IN QUERY FILE CONSISTENCY !!\n");
		exit(-1);
	}
	int temp;
	for(int i=0;i<n;i++){
		fscanf(f,"%d",&temp);
		// printf("%d ",temp );
		if(temp == 1){
			// printf("We are here\n");
			adjacencyvector[i] = true;
		}
	}
	// scanf("%d",&temp);
	return;
}
void getRankedList(FILE *f,int *rankedList,int *query,int n){
	fscanf(f,"%d",query);
	int temp;
	for(int i=0;i<n;i++){
		fscanf(f,"%d",rankedList+i);
	}
	return;
}
void computePrecision(const char *rankfile,const char *queryadjanceny,int qSize,int n){
	FILE *rank = fopen(rankfile,"r");
	FILE *queryfile = fopen(queryadjanceny,"r");

	bool adjacencyvector[n];
	int rankedList[n];
	int query;
	double precision[n];
	double recall[n];
	double meanaverageprecision = 0;
	for(int i=0;i<qSize;i++){
		getRankedList(rank,rankedList,&query,n);
		getAdjacencyVector(query,adjacencyvector,n,queryfile);
		/********** caclucate precision for the ith query *****************/
		int relevant = 0; // it will count relevant items for i th query
		int totalrelevant = 0; // it will store total number of relevant items for ith query
		double averageprecision = 0;// it will be the average precision for i th query
		for(int j=0;j<n;j++){
			if(adjacencyvector[j]){
				totalrelevant++;
			}
		}
		// printf("TOTAL RELEVANT = %d\n",totalrelevant );
		if(totalrelevant == 0){
			averageprecision = 0;
		}else{
			// printf("We are here\n");
			averageprecision = 0;
			relevant = 0;
			for(int j=0;j<n;j++){
				if(adjacencyvector[rankedList[j]]){
					// printf("We are here22\n");
					relevant++;
				}
				precision[j] = ((double)relevant)/((double)(j+1));
				// if(precision[j] > 0){
				// 	printf("%lf\n",precision[j] );
				// }
				recall[j] = ((double)relevant)/((double)totalrelevant);
			}
			for(int j=0;j<n;j++){
				// calulating the average precision for the ith query
				if(adjacencyvector[rankedList[j]]){
					// we are here
					// printf("We are here 11 precision = %lf\n",precision[j]);
					averageprecision = averageprecision + precision[j];
				}
			}
			averageprecision = (averageprecision/(double)totalrelevant);
		}
		meanaverageprecision = meanaverageprecision + averageprecision;
	}
	meanaverageprecision = meanaverageprecision / qSize;
	printf("MAP = %lf %%\n",meanaverageprecision * 100 );
	fclose(rank);
	fclose(queryfile);
	return;
}


int main(){
	Set Query = Set(QUERYFILE);
	extractQueryAdjacency(Query,ADJACENCYFILE,QUERYADJACENCY,N);
	if(PRIMALFORMAT == USELIBLINEAR){
		initNodeFeaturesMatrix(N,F);
		getNodeFeaturesFromFile(N,F,FEATUREFILE);
		rank_Liblinear(MODELFILE,QUERYADJACENCY,RANKFILE,Query,F,N,6);
		computePrecision(RANKFILE,QUERYADJACENCY,Query.getSize(),N);
	}
	return 0;
}