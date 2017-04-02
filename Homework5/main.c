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

  int i, j,  physicalMemory, runs, timeUnit, randSeed, size, duration;
  int firstProbe, firstFrag, firstProbeAvg, firstFragAvg, firstFailAvg, firstProbeTotal = 0,firstFailTotal = 0,	firstFragTotal = 0;
  int nextProbe, nextFrag, nextProbeAvg, nextFragAvg, nextFailAvg,nextProbeTotals = 0, nextFailTotals = 0, nextFragTotal = 0;
  int bestProbe, bestFrag, bestProbeAvg, bestFragAvg, bestFailAvg, bestProbeTotal = 0, bestFailTotal = 0, bestTotalFrag = 0;

  physicalMemory = atoi(argv[1]);
  runs = atoi(argv[2]);
  timeUnit = atoi(argv[3]);
  randSeed = atoi(argv[4]);
  mem_init(physicalMemory);
  srand(randSeed);

  for ( i = 0; i < runs; i++ ) {
    for ( j = 0; j < timeUnit; j++ ) {
      size = rand() % MAX_REQUEST_SIZE - MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION - MIN_DURATION;
      bestProbe = mem_allocate( BESTFIT, size, duration);
      if ( bestProbe == -1 ) {
        bestFailTotal += 1;
      }
      else if ( bestProbe != -1 ) {
	bestProbeTotal += bestProbe;
      }
      bestFrag = mem_fragment_count(MIN_REQUEST_SIZE - 1);
      bestTotalFrag += bestFrag;
      bestFragAvg = bestTotalFrag/runs;
      bestProbeAvg = bestProbeTotal/runs;
      bestFailAvg = bestFailTotal/runs;
      mem_single_time_unit_transpired();
      }
    mem_clear();
    for ( j = 0; j < timeUnit; j++ ) {
      size = rand() % MAX_REQUEST_SIZE - MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION - MIN_DURATION;
      firstProbe = mem_allocate( FIRSTFIT, size, duration);
      if ( firstProbe == -1 ) {
        firstFailTotal += 1;
      }
      else if ( firstProbe != -1 ) {
        firstProbeTotal += firstProbe;
      }
      firstFrag = mem_fragment_count(MIN_REQUEST_SIZE - 1);
      firstFragTotal += firstFrag;
      firstFragAvg = firstFragTotal/runs;
      firstProbeAvg = firstProbeTotal/runs;
      firstFailAvg = firstFailTotal/runs;
      mem_single_time_unit_transpired();
    }
    mem_clear();

    for ( j = 0; j < timeUnit; j++ ) {
      size = rand() % MAX_REQUEST_SIZE - MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION - MIN_DURATION;
      nextProbe = mem_allocate( NEXTFIT, size, duration);
      if ( nextProbe == -1 ) {
        nextFailTotals += 1;
      }
      else if ( nextProbe != -1 ) {
        nextProbeTotals += nextProbe;
      }
      nextFrag = mem_fragment_count(MIN_REQUEST_SIZE - 1); 
      nextFragTotal += nextFrag;
      nextFragAvg = nextFragTotal/runs;
      nextProbeAvg = nextProbeTotals/runs;
      nextFailAvg = nextFailTotals/runs;
      mem_single_time_unit_transpired();
      }
    mem_clear();
  }

  	printf("Best Avg Probes: %d\n", bestProbeAvg);
  	printf("Best Avg Fails %d\n", bestFailAvg);
  	printf("Best Avg Frags: %d\n", bestFragAvg);
  	printf("First Avg Probes: %d\n", firstProbeAvg);
  	printf("First Avg Fails %d\n", firstFailAvg);
  	printf("First Avg Frags: %d\n", firstFragAvg);
  	printf("Next Avg Probes: %d\n", nextProbeAvg);
  	printf("Next Avg Fails %d\n", nextFailAvg);
  	printf("Next Avg Frags: %d\n", nextFragAvg);




	mem_free();
	  
	return 0;
}
