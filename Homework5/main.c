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

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv){
  int i, j,memSize, simDur, numRun, randSeed;
  int exFragBest, numProbeBest, numAllocFailBest;
  int exFragFirst, numProbeFirst, numAllocFailFirst;
  int exFragNext, numProbeNext, numAllocFailNext;


  memSize = atoi(argv[1]);
  simDur = atoi(argv[2]);
  numRun = atoi(argv[3]);
  randSeed = atoi(argv[4]);

  mem_init(memSize);
  srand(randSeed);

  for(i = 0; i < simDur; i++){
    for(j = 0; j < numRun; j++){
    }
  }
  return 0;
}
