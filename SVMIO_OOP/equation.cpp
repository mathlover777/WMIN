#include "equation.h"
equation::equation(){
	equationString[0] = '\0';
	pointer = 0;
	outputFile[0] = '\0';
	maxSize = 100000;
	return;
}
void equation::setOutputFileName(const char *filename){
	sprintf(outputFile,"%s",filename);
	// printf("\noutput file {%s}\n",filename);
	// printf("\nfilename file {%s}\n",filename);
	return;
}
void equation::reset(int v){
	equationString[0] = '\0';
	pointer = 0;
	//outputFile[0] = '\0';
	sprintf(tempbuffer,"%d",v);
	append(equationString,&pointer,tempbuffer,maxSize);
	return;
}
void equation::add(int index,double value){
	// sprintf(tempbuffer," %d:%.16lf",index,value);
	sprintf(tempbuffer," %d:%lf",index,value);
	append(equationString,&pointer,tempbuffer,maxSize);
	return;
}
void equation::addToFile(){
	// printf("\nOutputFile : {%s}\n",outputFile);
	// printf("\nAppend:{\n%s}\n",equationString);
	addLine(outputFile,equationString);
	return;
}
void equation::print(){
	printf("\n%s",equationString);
	return;
}
/****************** non class functions ****************/
void resetBuffer(char *buffer,int *bufferPointer){
	buffer[0] = '\0';
	*bufferPointer = 0;
	return;
}
void append(char *a,int *i,const char *text,int maxlimit){
	// it is assumed that a[i] = '\0'
	// after completion a[i] will again be '\0'
	if(*i+strlen(text)>=maxlimit){
		printf("\nBUFFER SIZE NOT SUFFICIENT FOR GRAPH !!\n");
		exit(0);
	}
	int j = 0;
	while(text[j]!='\0'){
		a[*i] = text[j];
		j++;
		(*i)++;
	}
	a[*i] = '\0';
	return;
}