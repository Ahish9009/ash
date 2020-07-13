#include<stdio.h>
#include<unistd.h>

#include"utils.h"

bool validate_set_env(Cmd_s *cmd) {
	if (cmd->argc != 3) {
		fprintf(stderr, "Usage: set_env <name> <value>\n");
		return 1;
	}
	return 0;
}
bool validate_unset_env(Cmd_s *cmd) {
	if (cmd->argc != 2) {
		fprintf(stderr, "Usage: unset_env <name>\n");
		return 1;
	}
	return 0;
}
void set_env(Cmd_s *cmd) {

	if (validate_set_env(cmd)) return;
	
	if (setenv(cmd->argv[1], cmd->argv[2], 1) < 0) {
		perror("ash: set_env");
	}
	else {
		fprintf(stdout, GREEN "Successfully set %s=%s\n" CLR_RST, cmd->argv[1], cmd->argv[2]);
	}
}

void unset_env(Cmd_s *cmd) {
	if (validate_unset_env(cmd)) return;

	if (unsetenv(cmd->argv[1]) < 0) {
		perror("ash: unset_env");
	}
	else {
		fprintf(stdout, GREEN "Successfully unset %s\n" CLR_RST, cmd->argv[1]);
	}
}
