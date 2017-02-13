// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------
// void parse(char* line, command_t* p_cmd);
// int execute(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// void cleanup(command_t* p_cmd);


int stringsEqual(const char *a,const char *b){
	int i;
	for (i = 0; a[i] != '\0' && b[i] != '\0'; i++){
		if (a[i] != b[i]){
			return 0;
		}
	}

	return 1;
}



void parse(char* line, command_t* p_cmd){
	int i, j, argLength = 0, argCount = 1, argMan = 0;	
	//printf("Line = %s\n", line);
	for (i = 0; line[i] != '\0' && line[i] != '\n'; i++){ 
		if (line[i] == ' ' ){
			argCount++; 
			while (line[i] == ' '){ 
				i++;						
			}
		}
	}
	
	
	char **args = (char **)malloc(sizeof(char *) * (argCount +1));

	i = 0;
	while (argMan < argCount){
		
		argLength = 0;
		
		while(line[i + argLength] != ' ' && line[i + argLength] != '\n' && line[i + argLength] != '\0'){
			argLength++;
		}
		args[argMan] = (char*) malloc(sizeof(char) * (argLength + 1));
		
		for( j = i; j - i < argLength; j++){
			args[argMan][j-i] = line[j];
			//printf("line[j] = %d\n", line[j]);
			//printf("args[argMan][j-i] = ");
			//printf(args[argMan][j-i]);
			//printf("\n");
			
		}
		i = i + argLength;
		while(line[i] == ' '){
			i++;
		}		
		argMan++;
	}
	
	args[argCount] = NULL;
	//for(int l = 0; i < sizeof(args) - 1; l++){
	//	printf("args[%d] = %s\n", l, args[l]);
	//}
	
	
	

	(*p_cmd).name = args[0];
	printf("ARGS ZERO IS %s\n", args[0]);
	(*p_cmd).argc = argCount;
	(*p_cmd).argv = args;
	//printf("Everything got done peacefully. \n");
}

int execute(command_t* p_cmd){
	int found = 0;
	pid_t pid;
	char path[256];	
	if  (find_fullpath(path, p_cmd)){
		if (pid = fork() == 0){
			return execv(path, (*p_cmd).argv);
		}
		
		else{
			return wait(&pid);
		}
	}
	else{
		printf("Command not found.");
		return 127;
	}
	return -1;
}
 
int find_fullpath( char* fullpath, command_t* p_cmd){
	
	char *path = getenv("PATH\0");
	char *pathCheck = (char *) malloc(sizeof(char) * 256);
	int start = 0, i = 0, found = 0, j, k;	
	struct stat buffer;
	while (path[i] != '\0' && path[i - 1] != '\0' && !found){
		for (j = 0; j < 256; j++){
			pathCheck[j] = '\0';
		}
		int j = 0;
		while(path[i] != ':' && path[i] != '\0'){
			pathCheck[j] = path[i];
			i++;
			j++;
		}
		pathCheck[j] = '/';	
		k = 0;
		for (j += 1; (*p_cmd).name[k] != '\0'; j++){
			pathCheck[j] = (*p_cmd).name[k];
			k++;
		}	
		found = stat(pathCheck, &buffer) + 1;	
		if (found && (buffer.st_mode & S_IFREG)){
			
			for (j = 0; pathCheck[j] != '\0'; j++){
				fullpath[j] = pathCheck[j];
			}	
			fullpath[j] = '\0';
			return 1;
		}
		start = ++i;
	}
	free(pathCheck);
	return 0;
}

int is_builtin(command_t* p_cmd){
	int i;	
	for (i = 0; valid_builtin_commands[i] != NULL; i++){
		//printf("Please execute. The string we're looking at is: %s \n", (*p_cmd).name);
		
		if (stringsEqual(valid_builtin_commands[i], (*p_cmd).name)){
			//printf("IS BUILTIN PASSED\n");
			
			return 1;
		}
	}
	//printf("Do we die here?\n");
	return 0;
}

int do_builtin( command_t* p_cmd ){
	int found;

	if ((stringsEqual((*p_cmd).name, "cd"))){
		//printf("Did you get here now?\n");
		found = chdir((*p_cmd).argv[1]);
		//printf("Found is now:  %d\nAnd argv[1] is: %s\n", found, (*p_cmd).argv[1]);
		printf("arv[1] = %s\n", (*p_cmd).argv[1]);
		if (found == 0){
			printf("Successful\n");
			return SUCCESSFUL;
		}
		return ERROR;
	}

	return ERROR;
}

void cleanup(command_t* p_cmd){
	int i;

	for(i = 0; (*p_cmd).argv[i] != NULL; i++){
		
		//printf("Cleaning this arg[%d] = %s\n", i, (*p_cmd).argv[i]);	
		free((*p_cmd).argv[i]);	
		//printf("I died here.\n");	
	}
	//printf("I died here.\n");
	free((*p_cmd).argv);
}



			

