CSCI 340 Project by Vincent Nguyen and Daniel Feliciano

PAGE_SIZE was found using
	$ getconf PAGESIZE
TOTAL_MEM_SIZE was found using
	$ sudo cat /proc/meminfo



gettimeofday() gives the number of seconds and microseconds since the Epoch
	http://man7.org/linux/man-pages/man2/gettimeofday.2.html


1. How big is a cache block?
	C expands things out into conceptual rows, so to find a cache block, we tried to access the next thing
	outside the block. We increased how far ahead in the array we would go and see the time difference.
	There is a big jump in access time from 32 to 64, so we think a cache block is 32.

2. How big is the cache?
	We tried to access blocks of data that get bigger and bigger until they're larger than the L1 Cache size. And supposedly,
	we'll find a jump in the access times when we cross the cache.
	32K based on the output of the program.

3. How long does a refgerence to main memory take to complete?
	We assumed that making the program go through a 2d array all over the place,
	the next value it picks would not be in the cache.
	20-25 ns
	Although we think this may be the infamous L3 Cache rather than main memory.
4. How long does a reference that can be satisfied from cache take to complete?
	We assumed making the cache go through an array linearly would make it use the cache.
	2.5-3.0 ns 


