#include<stdio.h>
#include<unistd.h>

#include"utils.h"

bool validate_cd(Cmd_s *cmd) {
	
	if (cmd->argc > 2) {
		fprintf(stdout, "Usage: cd <dir>\n");
		return 1;
	}
	return 0;
}

void cd(Cmd_s *cmd) {

	if (validate_cd(cmd)) return;
	
	char *path;
	if (cmd->argc == 1) {
		path = home_path;
	}
	else {
		path = cmd->argv[1];
	}

	if (chdir(path)) {
		perror("ash: cd");
	}

}

