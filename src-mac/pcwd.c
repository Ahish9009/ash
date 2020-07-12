#include<stdio.h>
#include<unistd.h>

#include"utils.h"

bool validate_pwd(Cmd_s *cmd) {

	if (cmd->argc > 1) {
		fprintf(stderr, "Usage: pwd\n");
		return 1;
	}
	return 0;
}

void pwd(Cmd_s *cmd) {

	if (validate_pwd(cmd)) return;

	char *buf = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	if (!getcwd(buf, MAX_INPUT_SIZE)) {
		perror("ash: pwd");
		return;
	}
	fprintf(stdout, "%s\n", buf);
	free(buf);

}

