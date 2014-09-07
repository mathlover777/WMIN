#ifndef OTHER__
#define OTHER__

#include <stdio.h>
#include <stdlib.h>
#include <vector>

std::vector<int> selectKItems(std::vector<int> stream, int n, int k);
int nearestInteger(double d);
void loadBar(int x, int n, int r, int w);

class Clock{
private:
	clock_t begin, end;
public:
	void start();
	void reset();
	void show();
};
#endif