#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>

#include "utils.h"

void tokenize(char *inp, int *n, char **argv, char *delim) {
	
	char *temp = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	strcpy(temp, inp);
	char *token = strtok(temp, delim);
	*n = 0;
	while (token != NULL) {
		fprintf(stderr, "token: %s\n", token);
		
		argv[(*n)++] = token;
		token = strtok(NULL, delim);
	}
	argv[*n]=0;

	if (DEBUG) {
		fprintf(stderr, "___________\n");
		fprintf(stderr, "argc:\n%d\nargv:\n", *n);
		for (int i = 0; i < *n; i++) {
			fprintf(stderr, "%s\n", argv[i]);
		}
		fprintf(stderr, "___________\n");
	}

}

Commands_s * get_commands(Commands_s *commands, char *inp) {

	bool in_sq=0, in_dq=0, esc=0;
	int s=0, len = strlen(inp); 
	commands->cnt=0;

	for (int i = 0; inp[i] != 0; i++) {
		if (inp[i] == '\'') in_sq = !in_sq;
		if (!in_sq && inp[i] == '\"') in_dq = !in_dq;
		if (i == len-1 || (inp[i] == ';' && !(esc | in_dq | in_sq))) {

			Cmd_s *new_cmd = (Cmd_s*) malloc (sizeof(Cmd_s));
			new_cmd->argc = (int *) malloc (sizeof(int));
			new_cmd->full_cmd = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			new_cmd->argv = (char **) malloc (MAX_TOKENS*sizeof(char *));

			strcpy(new_cmd->full_cmd, inp);
			new_cmd->full_cmd[i]=0; new_cmd->full_cmd+=s;
			new_cmd->full_cmd = strip(new_cmd->full_cmd);

			tokenize(new_cmd->full_cmd, new_cmd->argc, new_cmd->argv, " ");
			if (!is_empty(new_cmd->full_cmd)) {
				commands->cmd_lst[commands->cnt++] = new_cmd;
			}

			s=i+1;
		}
		if (inp[i] == '\\') esc = !esc;
	}
	return commands;
}

Commands_s * parse(char *inp) {
	
	Commands_s *commands = (Commands_s*) malloc(sizeof(Commands_s));
	commands->cmd_lst = (Cmd_s**) malloc (MAX_BUFFER_CMDS*sizeof(Cmd_s*));
	commands = get_commands(commands, inp);
	return commands;
}
