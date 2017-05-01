#define PAGE_SIZE 8192
#define TOTAL_MEM_SIZE 4194304
#define L1_CACHE_LINE_SIZE 32

int cacheSize(int n, int run);
double cacheMemory();
double mainMemory();
int gettimeofday(struct timeval *tv, int k);
