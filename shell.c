#include<stdlib.h>
#include"utils.h"

int main(int argc, char **argv) {
	/*  
	 *  Main loop for the shell
	 */

	// initialize	
	init();	
	
	// main loop
	repl();

	//exit commands
	/*exit_shell();*/

	return EXIT_SUCCESS;
}
