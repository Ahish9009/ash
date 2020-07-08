#include<sys/wait.h>
#include<stdio.h>

#include"processes.h"
#include"prompt.h"

void bg_exit() {

	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG); 

	if (pid > 0 && find(pid)) {

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 0) {
				fprintf(stderr,  GREEN "Process with pid %d exited succesfully\n" CLR_RST, pid);
			}
		}
		fprintf(stderr, "%s", get_prompt());
	}


}
