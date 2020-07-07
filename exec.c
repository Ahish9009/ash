#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>

#include"utils.h"

int launch_process(char **args) {
	
	pid_t pid, wpid;
	int status;

	pid = fork();
	//child process
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("ash");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		perror("ash");
	}
	else {
		do {
		wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

void exec_piped(Commands_s *commands) {

	for (int i = 0; i < *commands->cnt; i++) {
		
		Piped_s *curr = commands->cmd_lst[i];
		if (!*curr->cnt) return;
		if (*curr->cnt == 1) {
			launch_process(curr->cmd_lst[0]->argv);
		}
	}

}
