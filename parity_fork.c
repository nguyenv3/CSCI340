#include <stdio.h>     // for printf()
#include <unistd.h>    // for fork(), pid_t
#include <stdlib.h>    // for exit()
#include <sys/types.h>
#include <sys/wait.h>  // for waitpid()


#define PARITY (const char*[2]){"EVEN", "ODD"}
#define DEBUG 0
int LIMIT;
int bitsum = 0;
int count_bits(int n){
  int bitn; 
  pid_t pidn_1, pidn_2; 
  int status;  

  if ((pidn_1 = fork()) == 0){ 
    if ( n == 0){
      exit(n);
    }  
    if (n % 2 == 0){    
      count_bits(n/2);      
    }
    else{
      bitsum = bitsum + 1;
      count_bits(n/2);       
    }
  }
  
  while (waitpid(pidn_1, &status, 0) > 0) {     
    if (WIFEXITED(status)){
      bitn = WEXITSTATUS(status);            
   }  
  }

#ifdef DEBUG
//  printf("bit from pod %d = %d\n", getpid(), n);
#endif
  if(n == 0){    
    printf("The number %d has %s parity\n" , LIMIT, PARITY[bitsum%2]);    
 }  
 exit(bitn);
}

  
int main(int argc, char** argv)
{
  int val;
  int n;
  if (argc == 1 || (val = atoi(argv[1])) < 0){    
    printf("USAGE: c BinaryParity non-negative-integer\n");
    return 0;
  }
  else{
    LIMIT = val;
    n = count_bits(val); 
    return 0;
  }
}
