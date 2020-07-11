#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include"utils.h"
#include"pwd.h"

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
	if (cmd->argc == 1) path = home_path;
	else if (!strcmp(cmd->argv[1], "~")) path = home_path;
	else if (!strcmp(cmd->argv[1], "-")) path = old_path;
	else path = cmd->argv[1];

	char *temp = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	getcwd(temp, MAX_INPUT_SIZE); 

	if (chdir(path)) {
		perror("ash: cd");
	}

	strcpy(old_path, temp);
	free(temp);
}

