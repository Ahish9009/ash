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
			\n5. bg [<pid>] \
			\n6. history \
			\n7. jobs \
			\n8. kjob \
			\n9. overkill \
			\n10. cd [dir] \
			\n11. pinfo [<pid>]\
			\n12. cronjob -c [cmd] -t [time] -p [period]\
			\n" \
			CLR_RST);
}
