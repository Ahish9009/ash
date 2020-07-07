#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>

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

