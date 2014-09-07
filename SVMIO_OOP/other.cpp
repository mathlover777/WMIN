#include "other.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "config.h"


std::vector<int> selectKItems(std::vector<int> stream, int n, int k){
	std::vector<int> reservoir(k);
	int i;
	for(i=0;i<k;i++){
		reservoir[i] = stream[i];
	}
	srand(time(NULL));
	for (; i < n; i++)
    {
        int j = rand() % (i+1);
        if (j < k){
          reservoir[j] = stream[i];
		}
    }
    return reservoir;
}
int nearestInteger(double d)
{
  return (int)floor(d + 0.5);
}
void loadBar(int x, int n, int r, int w){
    // Simple Inline ProgressBar Code
    // Process has done i out of n rounds,
    // and we want a bar of width w and resolution r.
    // Only update r times.
    if(PRINTMSG != VERBOSE){
        return;
    }
    if(x==0){
    	return;
    }
    int l = n/r;
    if(l == 0){
    	while(n<r){
    		n = n*2;
    		x = x*2;
    	}
    	l = n/r;
    }
    if ( x % (l) != 0 ) return;
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
    // Show the load bar.
    for (int x=0; x<c; x++)
       printf("=");
    for (int x=c; x<w; x++)
       printf(" ");
    // ANSI Control codes to go back to the
    // previous line and clear it.
    printf("]\n\033[F\033[J");
}

void Clock::start(){
	Clock::reset();
	return;
}
void Clock::reset(){
	begin = clock();
	return;
}
void Clock::show(){
	end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTIME ELLAPSED : %lf Second(s)\n",time_spent);
	return;
}