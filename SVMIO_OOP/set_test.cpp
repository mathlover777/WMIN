#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

int main(){
	Set A;
	Set B;

	A.print();

	A.fillRandom(10,15);
	B.fillRandom(8,15);

	A.removeDuplicates();
	B.removeDuplicates();

	A.print();
	B.print();

	// Set C;

	// C.add(100);
	// C.print();
	// C = A;

	// A.removeDuplicates();
	// A.print();
	// C.print();

	

	Set Inter = A * B;
	Inter.print();


	Set AminusB = A - B;
	Set BminusA = B - A;
	Set Total = (A - B) + (A*B) + (B - A);
	Total.print();
	Set Union = A + B;
	Union.print();
	


	AminusB.print();
	BminusA.print();


	return 0;
}