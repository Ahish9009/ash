#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>

#include"processes.h"
#include"prompt.h"

void bg_exit() {

	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG); 

	if (pid > 0 && find_bg(pid)) {

		Process_node *proc = get_bg(pid);
		char *name = (proc) ? proc->name : "Process";

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 0) 
				fprintf(stderr,  YELLOW "%s " GREEN "with pid" YELLOW " %d " GREEN "exited normally with status %d\n" CLR_RST, name, pid, status);
			else 
				fprintf(stderr,  YELLOW "%s " GREEN "with pid" YELLOW " %d " GREEN "exited with status %d\n" CLR_RST, name, pid, status);
		}
		fprintf(stderr, "%s", get_prompt());
		delete_proc(pid);
	}
	else if (pid > 0) {
		delete_proc(pid);
	}
}
void ctrl_c() {
	fprintf(stderr, "Exited\n");
	/*fprintf(stdout, "%s", get_prompt());*/
	/*fflush(stdout);*/
}
void ctrl_z() {

	

}
