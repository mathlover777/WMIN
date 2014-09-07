#ifndef VECTORARRAY
#define VECTORARRAY

#include <vector>
#include <stdio.h>
#include <stdlib.h>

class vectorarray{
private:
	std::vector<double> v;
public:
	vectorarray();
	vectorarray(int n);
	vectorarray(const vectorarray &u);
	vectorarray(const double *array,int size);
	int getSize();
	void reset(int n);
	void print();
	double get(int i);
	void set(int i,double x);
	void set(double x);
	//void copyToArray(double *n,int &size);
	vectorarray operator= (const vectorarray &u);
	vectorarray operator+(const vectorarray &a);
	vectorarray operator-(const vectorarray &a);
	vectorarray operator*(const double &x);
	vectorarray operator/(const double &x);
	double operator*(const vectorarray &x);
};
#endif