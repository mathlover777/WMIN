#include <stdlib.h>
#include <stdio.h>
#include "vectorarray.h"

int main(){
	double a[4];
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;

	double b[4];
	b[0] = 10;
	b[1] = 20;
	b[2] = 30;
	b[3] = 40;

	vectorarray A(a,4);
	vectorarray B(b,4);
	vectorarray C(4);


	A.print();
	B.print();
	C.print();

	vectorarray D = vectorarray(A);
	A = A - B;

	A.print();
	D.print();

	D.reset(6);
	D.print();
	
	return 0;
}