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


// -----------------------------------
// Main function 
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//
//
int main( int argc, char** argv ) {

	// ----------------------------------
	// Pseudocode
	// ----------------------------------
	// while ( !done )
	//		print the prompt (i.e. >, #, or $ ... your choice)
	//		read command line
	//		parse the command line
    //      if (parsed command is "exit")
    //      	done = true
	//  	else if ( is _builtin( ... ) )
	//			do_builtin( ... )
	//		else if ( find_fullpath( ... ) )
	//  		execute( ... )
	//		else
	//			error()
	// 		cleanup( ... )
	//
	int done = 0, i = 0, status;
	char line[256], path[256];
	command_t cmd;
	while(!done){
		printf("$ ");
		fgets(line, sizeof(line), stdin);
		//printf("line = %s\n", line);

		if (line[0] != '\n'){
			parse(line, &cmd);
		
			if (stringsEqual(cmd.name, "exit")) {
				done = 1;
			}
			else if (is_builtin(&cmd)){
				status = do_builtin(&cmd);
			}
			else if (find_fullpath(path, &cmd)){
				execute(&cmd);
			}
			else{
				printf("Command not found.\n");
			}
			cleanup(&cmd);
			for (i = 0; i < sizeof(line); i++){
				path[i] = '\0';
			}
		}
	}

	return 0;

}
// end main function

