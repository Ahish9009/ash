#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include"utils.h"
#include"redirect.h"
#include"processes.h"

int launch_process(Cmd_s cmd) {

	//set redirects
	set_redirect(cmd);
	
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
		if (execvp(args[0], args) == -1) {
			perror("ash");
		}
		exit(EXIT_FAILURE);
	}
	else {
		if (!cmd.in_bg) {

			tcsetpgrp(shell_term, pid);
			waitpid(pid, &status, WUNTRACED);	
			tcsetpgrp(shell_term, shell_pid);
		}
		else {
			setpgid(pid, pid);
			Process_node *node = (Process_node *) malloc(sizeof(Process_node));
			node->pid = pid;
			node->name = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			strcpy(node->name, cmd.argv[0]);
			node->root = 0;
			node->next = 0;
			insert(node);
		}

	}

	unset_redirect(cmd);
	return 1;
}

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

		launch_process(*curr.cmd_lst[i]);
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
			launch_process(*curr->cmd_lst[0]);
		}
		else {
			launch_piped(*curr);
		}
	}
}
