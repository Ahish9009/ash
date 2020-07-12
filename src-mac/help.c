#include<stdio.h>

#include"utils.h"


void help(Cmd_s *cmd) {
	
	if (cmd->argc > 1) {
		fprintf(stderr, "Usage: help\n");
		return;
	}

	fprintf(stdout, GREEN "Supported built-in commands: \
			\n1. ls -[al] \
			\n2. echo -[n] [string...] \
			\n3. pwd \
			\n4. fg [<pid>] \
			\n5. history \
			\n6. jobs \
			\n7. kjob \
			\n" \
			CLR_RST);
}
