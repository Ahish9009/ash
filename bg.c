#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <signal.h>

#include"utils.h"
#include"processes.h"

void bg(Cmd_s *cmd) {

	if (cmd->argc != 2) {
		fprintf(stderr, "Usage: bg <job id>\n");
		return;
	}

	int n = atoi(cmd->argv[1]);
	Process_node *proc = get_by_ind(n);

	if (!proc) {
		fprintf(stderr, "Process %s couldn't be found\n", cmd->argv[1]);
		return;
	}
	
	tcsetpgrp(shell_term, shell_pid);

	cmd->in_bg = 1;
	proc->bg = 1;
	
	setpgid(proc->pid, proc->pid);
	if (kill(proc->pid, SIGCONT)) {
		perror("ash: bg");
		return;
	}

}
