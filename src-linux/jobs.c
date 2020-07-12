#include<stdio.h>

#include"utils.h"
#include"processes.h"

void jobs(Cmd_s *cmd) {

	if (cmd->argc > 1) {
		fprintf(stderr, "usage: jobs\n");
		return;
	}

	display();
}
