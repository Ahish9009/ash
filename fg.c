#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<termios.h>

#include"utils.h"
#include"processes.h"

void fg(Cmd_s *cmd) {

	if (cmd->argc != 2) {
		fprintf(stderr, "Usage: fg <job id>\n");
		return;
	}

	int n = atoi(cmd->argv[1]);
	Process_node *proc = get_proc_ind(n);

	if (!proc) {
		fprintf(stderr, "Process %s couldn't be found\n", cmd->argv[1]);
		return;
	}

	int status;
	cmd->in_bg = 0;
	proc->bg = 0;
	tcsetpgrp(shell_term, proc->pid);
	if (kill(proc->pid, SIGCONT)) {
		perror("ash: fg");
		return;
	}
	waitpid(proc->pid, &status, WUNTRACED);	
	tcsetpgrp(shell_term, shell_pid);

}
