#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"


//float times[18];


int cacheSize(int n, int run) {
	float totalTime;
	int *a, *b, i, j, cacheLineGuess, iterate;
	struct timeval time1, time2;
	

    	cacheLineGuess = n;
    	a = (void*)malloc(TOTAL_MEM_SIZE);
	b = (void*)malloc(TOTAL_MEM_SIZE);

    	for(i = 0; i < TOTAL_MEM_SIZE/PAGE_SIZE; i++){
        	*a = 1;
		a = a + 2048;
	}

   	iterate = TOTAL_MEM_SIZE / (cacheLineGuess * L1_CACHE_LINE_SIZE); 
    	gettimeofday(&time1,0);
	a = b;
    	for(i = 0; i < iterate; i++) {
		a = b;
	
        	for(j = 0; j < cacheLineGuess; j++){        		
			a = a + 0;
		}
   	}
	

   	gettimeofday(&time2,0);

  	totalTime = ((time2.tv_sec-time1.tv_sec)*1000000 + (time2.tv_usec-time1.tv_usec));
	
    	printf("Access time for block size = %d : %f seconds\n", cacheLineGuess * L1_CACHE_LINE_SIZE, totalTime/iterate); 
	//times[run] = (totalTime/iterate);
	//printf("totalTime/iterate = %f\n", totalTime/iterate);
	return 0;
	
	
}

double mainMemory(int k) {
	int i,j;
	double totalTime2;
	clock_t time2;
	static int x[10000][10000];

	time2 = clock();
	//printf("died at main memory");
	
	for (i = 0; i < 10000; i++) {
		for (j = 0; j < 10000; j++) {
			x[j][i] = i + j;

		}
  	}

/*	for (j = 0; j < 10000; j++) {
		for (i = 0; i < 10000 - 1; i++) {
			x[j][i] = i + j;
			
		}
	}	
*/
	

	
	time2 = clock() - time2;

	totalTime2 = ((double)time2)/CLOCKS_PER_SEC;

	printf("\nTime to complete in Main memory #%d: %f seconds\n",k + 1, totalTime2);
	return totalTime2/(10000*10000);
	
}

double cacheMemory(int k) {
	int i,j;
	double totalTime;
	clock_t time;
	static int x2[10000][10000];

	time = clock();
	//printf("Start clock = %ld\n", time);
	//printf("died at cache");
	for (j = 0; j < 10000; j++) {
		for (i = 0; i < 10000; i++) {
			x2[j][i] = i + j;
			
		}
	}
	//time = clock();
	//x2[0][10000-1] = 0 + 0;
	
	time = clock() - time;
	//printf("End clock = %ld\n", time);
	totalTime = ((double)time)/CLOCKS_PER_SEC;
	printf("\nTime to complete in Cache memory access time #%d: %f second\n",k + 1, totalTime);
	return totalTime/(10000*10000);
	
}



int main(){
	int i,j, guessSize;
	double cacheSum = 0, mainSum = 0;
	for(i = 0; i < 17; i++){
		guessSize = pow(2, i);
		printf("\n\nTrying size of block %d\n\n", guessSize);
		for(j = 0; j < 10; j++){
			cacheSize(guessSize, i);
		}		
	}
	
/*	for(i = 0; i < 18 - 1; i++){
		time1 = times[i];
		time2 = times[i+1];
		if((t = abs(time1-time2))> timeDiff){
			printf("true\n");
			timeDiff = t;
		}	
		
	}
	printf("timeDiff = %f\n", timeDiff);
*/
	//printf("alive\n");
	for(i = 0; i < 10; i++){
		cacheSum = cacheSum + cacheMemory(i);
	}
	
	for(i = 0; i < 10; i++){
		mainSum = mainSum + mainMemory(i);
	}
	printf("\nAverage cache memory access time was: %f ns\n", (cacheSum/10)*1000000000);
	printf("\nAverage main memory access time was: %f ns \n", (mainSum/10)*1000000000);
	return 0;
}
