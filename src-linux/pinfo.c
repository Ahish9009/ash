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

	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "executable: %s\n", exe);


}
