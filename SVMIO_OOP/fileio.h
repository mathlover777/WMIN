#ifndef __FILEIO__
#define __FILEIO__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*****************FILE read write functions**************************/
void readLine(FILE *fp,char *line,int *endflag);
void clearTabs(char *line);
FILE* initializeFileRead(const char *filename,int *fileflag);
void resetFile(const char *x);
void addLine(const char *filename,const char *line);
int isExist(const char *FILENAME);
#endif