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
	Process_node *proc = get_by_ind(n);

	if (!proc) {
		fprintf(stderr, "Process %s couldn't be found\n", cmd->argv[1]);
		return;
	}

	int status;
	cmd->in_bg = 0;
	proc->bg = 0;

	if (kill(proc->pid, SIGCONT)) {
		perror("ash: fg");
		return;
	}

	tcsetpgrp(shell_term, proc->pid);
	tcsetpgrp(STDIN_FILENO, proc->pid);
	tcsetpgrp(STDOUT_FILENO, proc->pid);

	waitpid(proc->pid, &status, WUNTRACED);	

	tcsetpgrp(shell_term, shell_pid);
	tcsetpgrp(STDIN_FILENO, shell_pid);
	tcsetpgrp(STDOUT_FILENO, shell_pid);

	if (WIFSTOPPED(status)) {
		setpgid(proc->pid, proc->pid);
		proc->bg = 1;
		fprintf(stderr, "\nstopped  %s [%d]\n", proc->name, proc->pid);
	}
}
