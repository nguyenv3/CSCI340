CSCI 340 Project by Vincent Nguyen and Daniel Feliciano

PAGE_SIZE was found using
	$ getconf PAGESIZE
TOTAL_MEM_SIZE was found using
	$ sudo cat /proc/meminfo
L1_CACHE_LINE_SIZE is known to be 64.


gettimeofday() gives the number of seconds and microseconds since the Epoch
	http://man7.org/linux/man-pages/man2/gettimeofday.2.html


Based on the sample output below when we ran this program,
we assumed the cache size is 32k because the access time results
were very close to each other compared to the 64k where there is
high variation between access time with a ridiculously high outlier.
1. How big is a cache block?
	Unable to find through experimentation, so we used $ getconf PAGESIZE

2. How big is the cache?
	32K based on the output of the program. The size 32K usually only had one outlier indicating we stepped out the cache.

3. How long does a refgerence to main memory take to complete?
	We assumed that making the program go through a 2d array all over the place,
	the next value it picks would not be in the cache.
	15-20 ns
	Although we think this may be the infamous L3 Cache rather than main memory.
4. How long does a reference that can be satisfied from cache take to complete?
	We assumed making the cache go through an array linearly would make it use the cache.
	0.5-3.0 ns 


