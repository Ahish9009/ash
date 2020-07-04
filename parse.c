#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>

#include "utils.h"

/*Commands_s commands;*/

void strip(char *x) {

	while (*x == ' ') x++;
	int len = strlen(x);
	while (len > 0 && x[len]==' ') len--;
	x[len]=0;

	printf("len: %d\n", len);
}

Commands_s * get_commands(Commands_s *commands, char *inp) {

	bool in_sq=0, in_dq=0, esc=0;
	int s=0; 
	commands->cnt=0;

	for (int i = 0; inp[i] != 0; i++) {
		if (inp[i] == '\'') in_sq = !in_sq;
		if (inp[i] == '\"') in_dq = !in_dq;
		if (inp[i] == ';' && !(esc | in_dq | in_sq)) {

			Cmd_s *new_cmd = (Cmd_s*) malloc(sizeof(Cmd_s));
			new_cmd->full_cmd = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));

			strcpy(new_cmd->full_cmd, inp);
			new_cmd->full_cmd[i]=0; new_cmd->full_cmd+=s;
			strip(new_cmd->full_cmd);

			commands->cmd_lst[commands->cnt++] = new_cmd;

			s=i+1;
		}

		// handle escaping
		esc = 0;
		if (inp[i] == '\\') {
			if (esc) esc = 0;
			else esc = 1;
		}
		
	}
	for (int i = 0; i < commands->cnt; i++) 
		printf("%s\n", commands->cmd_lst[i]->full_cmd);

	return commands;
}

Commands_s * parse(char *inp) {
	
	Commands_s *commands = (Commands_s*) malloc(sizeof(Commands_s));
	commands->cmd_lst = (Cmd_s**) malloc (MAX_BUFFER_CMDS*sizeof(Cmd_s*));
	commands = get_commands(commands, inp);

	return commands;
}

int main() {
	
	char inp[] = "Hello worl \"d;c\'lolzor;\'o; \" mment allez vous?;     je vais bien  ; lolzor ;";
	parse(inp);

	printf("\n");

	return 0;

}
