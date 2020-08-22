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
	
	bool no_nl = 0;
	for (int i = 1; i < cmd->argc; i++) {
		if (!strcmp(cmd->argv[i], "-n")) no_nl = 1;
		if (cmd->argv[i][0] == '-') continue;
		fprintf(stdout, "%s ", cmd->argv[i]);
	}
	if (!no_nl) fprintf(stdout, "\n");

}
