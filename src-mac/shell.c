#include<stdlib.h>

#include"utils.h"

int main(int argc, char **argv) {

	// initialize	
	init();	
	
	// main loop
	repl();

	//exit commands
	shutdown();

	return EXIT_SUCCESS;
}
