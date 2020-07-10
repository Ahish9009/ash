#include<signal.h>
#include<stdio.h>
#include <sys/types.h>
#include <signal.h>

#include"utils.h"

void overkill(Cmd_s *cmd) {

	if (cmd->argc > 1) {
		fprintf(stderr, "Usage: overkill\n");
		return;
	}

	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next;
		if (kill(last->pid, SIGKILL)) {
			fprintf(stderr, "Process with pid %d couldn't be killed\n", last->pid);
		}
	}

}
