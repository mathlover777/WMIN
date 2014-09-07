#ifndef SOURAVSET
#define SOURAVSET

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>


class Set{
private:	
	std::vector<int> v;
public:
	Set();
	Set(const Set &S);
	Set(const char *filename); // assuming file is -1 terminated
	Set(const std::vector<int> vec);
	void reset();
	void add(int element);
	int getSize();
	void fillRandom(int n,int randMax);

	void removeDuplicates();
	void reduceSizeInPlace(double percentage);
	void sort();
	int getElement(int pos);
	std::vector<int> SetToVector();
	Set operator=(const Set &S);
	Set operator+(const Set &S); // union
	Set operator*(const Set &S); // intersection
	Set operator-(const Set &S); // minus
	void print();
};
#endif