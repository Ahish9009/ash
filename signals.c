#include<sys/wait.h>
#include<stdio.h>

#include"processes.h"
#include"prompt.h"

void bg_exit() {

	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG); 

	if (pid > 0 && find(pid)) {

		Process_node *proc = get(pid);
		char *name = (proc) ? proc->name : "Process";

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 0) {
				fprintf(stderr,  YELLOW "%s " GREEN "with pid" YELLOW " %d " GREEN "exited normally\n" CLR_RST, name, pid);
			}
		}
		fprintf(stderr, "%s", get_prompt());
		delete_proc(pid);
	}


}
