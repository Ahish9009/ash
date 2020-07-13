#include<stdio.h>

#include"utils.h"


void help(Cmd_s *cmd) {
	
	if (cmd->argc > 1) {
		fprintf(stderr, "Usage: help\n");
		return;
	}

	fprintf(stdout, GREEN "Supported built-in commands: \
			\n 1. ls -[al] \
			\n 2. echo -[n] [string...] \
			\n 3. pwd \
			\n 4. fg [<job id>] \
			\n 5. bg [<job id>] \
			\n 6. history \
			\n 7. jobs \
			\n 8. kjob \
			\n 9. overkill \
			\n10. cd [dir] \
			\n11. pinfo [<pid>]\
			\n12. cronjob -c [cmd] -t [time] -p [period]\
			\n13. set_env <name> <value>\
			\n14. unset_env <name>\
			\n" \
			CLR_RST);
}
