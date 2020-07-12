#include<stdio.h>
#include<unistd.h>
#include<ctype.h>

#include"utils.h"
#include"processes.h"

bool validate_pinfo(Cmd_s *cmd) {

	if (cmd->argc > 2) {
		fprintf(stderr, "Usage: pinfo <pid>\n");
		return 1;
	}
	return 0;
}

void pinfo(Cmd_s *cmd) {

	if (validate_pinfo(cmd)) return;

	int pid;
	if (cmd->argc == 1) pid = shell_pid;
	else pid = atoi(cmd->argv[1]);

	char *exe_path = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	sprintf(exe_path, "/proc/%d/exe", pid);

	char *exe = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	int l = readlink(exe_path, exe, MAX_INPUT_SIZE);
	exe[l] = 0;

	char *proc_fpath = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	sprintf(proc_fpath, "/proc/%d/stat", pid);

	FILE *fd = fopen(proc_fpath, "r");
	int *i = (int *) malloc (sizeof(int));	
	char *ign = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
	char status;
	long int vmem;

	fscanf(fd, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %ld", 
			&pid, ign, &status, 
			i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, 
			&vmem);

	fclose(fd);
	free(i);
	free(ign);

	char *status_desc;
	if (status == 'R') status_desc = "running";
	else if (status == 'T' || status == 't') status_desc = "stopped";
	else if (status == 'S') status_desc = "sleeping";
	else if (status == 'D') status_desc = "waiting";
	else if (status == 'Z') status_desc = "zombie";
	else status_desc = "other";


	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "status: %s\n", status_desc);
	fprintf(stdout, "memory: %ld\n", vmem);
	fprintf(stdout, "executable: %s\n", exe);


}
