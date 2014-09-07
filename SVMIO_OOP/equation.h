#ifndef __EQUATION__SOURAV__
#define __EQUATION__SOURAV__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

class equation{
private:
	char equationString[100000];
	char tempbuffer[10000];
	int pointer;
	char outputFile[1000];
	int maxSize;
public:
	equation();
	void setOutputFileName(const char *filename);
	void reset(int v);
	void add(int index,double value);
	void addToFile();
	void print();
};
/****************** non class functions ****************/
void resetBuffer(char *buffer,int *bufferPointer);
void append(char *a,int *i,const char *text,int maxlimit);
#endif