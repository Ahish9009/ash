#include<stdio.h>
#include<string.h>

#include"utils.h"

bool validate_echo(Cmd_s *cmd) {
	return 0;
}

void echo(Cmd_s *cmd) {

	if (validate_echo(cmd)) {
		fprintf(stderr, "Usage: echo [string ...]\n");
		return;
	}
	
	bool nl = 1;
	for (int i = 1; i < cmd->argc; i++) {
		if (!strcmp(cmd->argv[i], "-n")) nl = 0;
		else fprintf(stdout, "%s ", cmd->argv[i]);
	}
	if (nl) fprintf(stdout, "\n");

}
