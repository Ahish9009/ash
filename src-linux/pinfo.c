#include<stdio.h>
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


	fprintf(stdout, "pid: %d\n", pid);


}
