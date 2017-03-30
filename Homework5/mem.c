#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration){

  int i, count, start, block;
  int best, bestIndex;
  block = 0;
  if(strategy == BESTFIT){
    for(i=0; i < mem_size; i++){
      if((i !=0 && memory[i] == 0 && memory[i-1] != 0) || (i == 0 && memory[i] == 0)){
        start = i;
        block++;
        count = 0;
      }
      
      if(memory[i] == 0){
        count++;
      }
      else if(memory[i] != 0){
        count = 0;
      }
      if(size <= count){
        best = size - count;
        if(best >= 0 || count < best){
          bestIndex = start;
        }
        else{
          while(count !=0){
            memory[bestIndex] = duration;
            bestIndex++;
            count--;
           }
         }
       }
    }
  }
  else if(strategy == NEXTFIT){
    for(i = 0; i < mem_size; i++){
      if((i !=0 && memory[i] == 0 && memory[i-1] != 0) || (i == 0 && memory[i] == 0)){
        start = i;
        block++;
        count = 0;
      }
      if(memory[i] == 0){
        count++;
      }
      else if(memory[i] != 0){
        count = 0;
      }
      if(size <= count){
        last_placement_position = start;
        i = last_placement_position;
        while(count != 0){
          memory[start] = duration;
          start++;
          count--;
        }
      }
      if(last_placement_position == (mem_size-1)){
        last_placement_position = 0;
      }
    }
  }
  
        
  return block;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired(){
  
  int i;
  for(i = 0; i < mem_size; i++){
    if(memory[i] > 0){
      memory[i]--;
    }
  }
  return 0;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size){

  int i, fragCount, freeCount;
  for(i = 0; i < mem_size; i++){
    if(memory[i]==0){
      freeCount++;
    }
    else if(memory[i] != 0 && memory[i-1] == 0 && i > 0){
      if(freeCount < frag_size){
        fragCount++;
      }
      freeCount = 0;
    }
  }
  return 0;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear(){

  int i;
  for(i = 0; i < mem_size; i++){
    memory[i] = 0;
  }
  return;
}

/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
}

/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free()
{
  free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print(){

  int i;
  printf("mem_print()\n");

  for(i = 0; i < mem_size; i++){
    printf("|%d|", memory[i]);
  }
  printf("\n");
}
