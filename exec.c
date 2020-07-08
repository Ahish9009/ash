#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include"utils.h"
#include"redirect.h"
#include"processes.h"

#include"jobs.h"

int launch_process(Cmd_s cmd) {

	//set redirects
	
	pid_t pid;
	int status;

	char **args = cmd.argv;

	pid = fork();
	if (pid < 0) {
		perror("ash");
		return 1;
	}
	//child process
	if (pid == 0) {

		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
		if (execvp(args[0], args) == -1) {
			fprintf(stderr, "ash: '%s' is not a command\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else {
		Process_node *node = (Process_node *) malloc(sizeof(Process_node));
		node->pid = pid;
		node->name = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
		strcpy(node->name, cmd.argv[0]);
		node->root = 0;
		node->next = 0;

		if (!cmd.in_bg) {
			node->bg = 0;
			insert(node);

			tcsetpgrp(shell_term, pid);
			waitpid(pid, &status, WUNTRACED);	
			tcsetpgrp(shell_term, shell_pid);
		}
		else {
			setpgid(pid, pid);
			node->bg = 1;
			insert(node);
		}
	}

	return 1;
}

void handle_cmd(Cmd_s cmd) {

	set_redirect(cmd);
	if (!strcmp(cmd.argv[0], "jobs")) {
		jobs(cmd);
	}
	else launch_process(cmd);
	unset_redirect(cmd);
	
};

void launch_piped(Piped_s curr) {

	_STDIN = dup(STDIN_FILENO);
	_STDOUT = dup(STDOUT_FILENO);

	int n = *curr.cnt;
	int pipes[n-1][2];
	for (int i = 0; i < n-1; i++) {
		if (pipe(pipes[i])) { 
			perror("ash");
			return;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!i) {
			dup2(pipes[i][1], STDOUT_FILENO);
		}
		else if (i == n-1) {
			dup2(pipes[i-1][0], STDIN_FILENO);
			dup2(_STDOUT, STDOUT_FILENO);
		}
		else {
			dup2(pipes[i-1][0], STDIN_FILENO);
			dup2(pipes[i][1], STDOUT_FILENO);
		}

		handle_cmd(*curr.cmd_lst[i]);
		if (i != n-1) close(pipes[i][1]);
		if (!i) close(pipes[i-1][0]);
	}
	
	dup2(_STDIN, STDIN_FILENO);
}

void exec_piped(Commands_s *commands) {

	for (int i = 0; i < *commands->cnt; i++) {
		
		Piped_s *curr = commands->cmd_lst[i];
		if (!*curr->cnt) return;
		if (*curr->cnt == 1) {
			handle_cmd(*curr->cmd_lst[0]);
		}
		else {
			launch_piped(*curr);
		}
	}
}
