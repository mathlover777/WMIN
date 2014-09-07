#ifndef __CONFIG__SOURAV
#define __CONFIG__SOURAV

#define VERBOSE 1
#define NONVERBOSE 0
#define USEAB 1
#define USESB 0

#define USEPEGASOS 1
#define USELIBLINEAR 0


/************ for netflix data set ********************/
//#define ADJACENCYFILE "netflix_adjacency.txt"
//#define FEATUREFILE "netflix_feature.txt"
//#define QUERYFILE "netflix_query.txt"
//#define QUERYADJACENCY "netflix_query_adjacency.txt"
//#define N 17770
//#define F 64
//#define OUTPUTFILE "netflix_output.txt"
// #define MODELFILE "netflix_output.txt.model"
// #define RANKFILE "netflix_rank.txt"
/******************************************************/

/************ for movielens data set ******************/
#define ADJACENCYFILE "movielens_adjacency.txt"
#define FEATUREFILE "movielens_feature.txt"
#define QUERYFILE "movielens_query.txt"
#define QUERYADJACENCY "movielens_query_adjacency.txt"
#define MODELFILE "movielens_output.txt.model"
#define N 3952
#define F 18
#define OUTPUTFILE "movielens_output.txt"
#define RANKFILE "movielens_rank.txt"
/******************************************************/


/****************** RANDOM ****************************/
// use graphtest to generate the files
// #define ADJACENCYFILE "test_adjacency.txt"
// #define FEATUREFILE "test_feature.txt"
// #define QUERYFILE "test_query.txt"
// #define QUERYADJACENCY "test_query_adjacency.txt"
// #define N 1000
// #define F 18
// #define OUTPUTFILE "test_output.txt"
// #define MODELFILE "test_output.txt.model"
// #define RANKFILE "test_rank.txt"
/******************************************************/




/********** COMP PARAMS *******************************/
#define EDGEPERCENTAGE 0.8
#define NONEDGEPERCENTAGE 0.9
/******************************************************/

/*************** config settings **********************/
#define PRINTMSG 1
#define INTERSECTIONPART 0
/******************************************************/

/*************** primal program ***********************/
#define PRIMALFORMAT 0
// use 0 for liblinear and 1 for pegasos
/******************************************************/

#endif
