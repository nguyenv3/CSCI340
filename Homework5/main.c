#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 100 3000 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv){
  int i, j,memSize, size, duration, simDur, numRun, randSeed;
  int exFragBest = 0, numProbeBest = 0, numAllocFailBest = 0, numTotalProbeBest = 0, exFragTotalBest = 0, exFragBestAvg = 0, numProbeBestAvg = 0, numAllocFailBestAvg = 0;
  int exFragFirst = 0, numProbeFirst = 0, numAllocFailFirst = 0;
  int exFragNext = 0, numProbeNext = 0, numAllocFailNext = 0;
  

  memSize = atoi(argv[1]);
  numRun = atoi(argv[2]);
  simDur = atoi(argv[3]);
  randSeed = atoi(argv[4]);

  mem_init(memSize);
  srand(randSeed);
  
  for(i = 0; i < simDur; i++){
    for(j = 0; j < numRun; j++){
     size = rand() % (MAX_REQUEST_SIZE - MIN_REQUEST_SIZE);
     duration = rand() % (MAX_DURATION - MIN_DURATION);
     
     numProbeBest = mem_allocate(BESTFIT, size, duration);
     //printf("numProbeBest = %d\n", numProbeBest);
     if(numProbeBest == -1){
       numAllocFailBest += 1;
       printf("ALLOCATION OF BEST FAILED\n");       
     } 
    
     else if(numProbeBest != -1){
       numTotalProbeBest += numProbeBest;
     }

     exFragBest = mem_fragment_count(MIN_REQUEST_SIZE -1);
     exFragTotalBest += exFragBest;
     exFragBestAvg = exFragTotalBest/simDur;
     numProbeBestAvg = numTotalProbeBest/simDur;
     numAllocFailBestAvg = numAllocFailBest/simDur;
     mem_print();
     mem_single_time_unit_transpired(); 
     //mem_print();
     
     
     //printf("numAllocFailBest = %d\n", numAllocFailBest);
    }
  }
  return 0;
}
