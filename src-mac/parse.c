#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>

#include "utils.h"
#include"history.h"

void tokenize(Cmd_s *new_cmd, char *delim) {

	char *inp = new_cmd->full_cmd;
	int n = 0;
	
	char *temp = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	char *temp_start = temp;
	strcpy(temp, inp);
	char *token = strtok(temp, delim);
	int flag_out=0, flag_in=0, flag_q = 0;
	int s_i = 0, e_i = -1;
	while (token) {
		strip(token);

		if (check_quotes(token, flag_q)) {
			int ind = token - temp_start;
			if (flag_q && (check_quotes(token, flag_q) != flag_q)) {
				token = strtok(NULL, delim);
				continue;
			}
			if (!flag_q) {
				s_i = ind;
				flag_q = check_quotes(token, flag_q);
			}
			else {
				e_i = ind+strlen(token);
				char *q_token = (char *) malloc((e_i-s_i+2)*sizeof(char));
				new_cmd->argv[n++] = strncpy(q_token, inp+s_i, e_i-s_i + 1);
				replace_quotes(new_cmd->argv[n-1]);

				flag_q = 0;
				token = strtok(NULL, delim);
				e_i = -1;
				continue;
			}
		}
		if (flag_q) {
			token = strtok(NULL, delim);
			continue;
		};

		replace_quotes(token);

		if (flag_out) {
			new_cmd->f_out = token;
			if (flag_out == 2) new_cmd->a = 1;
			flag_out = -1;
		}
		if (flag_in) {
			new_cmd->f_in = token;
			flag_in = -1;
		}

		if (!strcmp(token, ">")) flag_out = 1;
		if (!strcmp(token, ">>")) flag_out = 2;
		if (!strcmp(token, "<")) flag_in = 1;
		if (!strcmp(token, "&")) {
			new_cmd->in_bg = 1;
			token = strtok(NULL, delim);
			continue;
		}
		if (token[strlen(token)-1] == '&') {
			new_cmd->in_bg = 1;
			token[strlen(token)-1] = 0;
		}
		
		if (!flag_out && !flag_in) new_cmd->argv[n++] = token;
		if (flag_in == -1) flag_in = 0;
		if (flag_out == -1) flag_out = 0;

		token = strtok(NULL, delim);
	}

	new_cmd->argv[n]=0;
	new_cmd->argc = n;

	free(token);
}

Piped_s * get_piped_commands(Piped_s *piped_commands, char *inp) {

	bool in_sq=0, in_dq=0, esc=0;
	int s=0, len = strlen(inp); 
	*piped_commands->cnt=0;

	for (int i = 0; inp[i] != 0; i++) {
		
		if (inp[i] == '\'') in_sq = !in_sq;
		if (!in_sq && inp[i] == '\"') in_dq = !in_dq;
		if (i == len-1 || (inp[i] == '|' && !(esc | in_dq | in_sq))) {

			Cmd_s *new_cmd = (Cmd_s*) malloc (sizeof(Cmd_s));
			new_cmd->full_cmd = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			new_cmd->argv = (char **) malloc (MAX_TOKENS*sizeof(char *));
			new_cmd->f_out = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			new_cmd->f_in = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			new_cmd->in_bg = 0;

			strcpy(new_cmd->full_cmd, inp);
			if (i == len-1 && inp[i] != '|') {
				new_cmd->full_cmd[i+1]=0; new_cmd->full_cmd+=s;
			}
			else { 
				new_cmd->full_cmd[i]=0; new_cmd->full_cmd+=s;
			}
			strip(new_cmd->full_cmd);

			tokenize(new_cmd, " ");
			if (!is_empty(new_cmd->full_cmd)) {
				piped_commands->cmd_lst[(*piped_commands->cnt)++] = new_cmd;
			}
			s=i+1;
		}
		if (inp[i] == '\\') esc = !esc;
	}

	return piped_commands;

}

Commands_s * get_commands(Commands_s *commands, char *inp) {

	bool in_sq=0, in_dq=0, esc=0;
	int s=0, len = strlen(inp); 
	*commands->cnt=0;

	for (int i = 0; inp[i] != 0; i++) {
		if (inp[i] == '\'') in_sq = !in_sq;
		if (!in_sq && inp[i] == '\"') in_dq = !in_dq;
		if (i == len-1 || (inp[i] == ';' && !(esc | in_dq | in_sq))) {

			Piped_s *piped_commands = (Piped_s*) malloc (sizeof(Piped_s));
			piped_commands->cnt = (int *) malloc (sizeof(int));
			piped_commands->full_cmd = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
			piped_commands->cmd_lst = (Cmd_s **) malloc (MAX_TOKENS*sizeof(Cmd_s *));

			strcpy(piped_commands->full_cmd, inp);
			if (i == len-1 && inp[i] != ';') {
				piped_commands->full_cmd[i+1]=0; piped_commands->full_cmd+=s;
			}
			else {
			piped_commands->full_cmd[i]=0; piped_commands->full_cmd+=s;
			}
			strip(piped_commands->full_cmd);

			piped_commands = get_piped_commands(piped_commands, piped_commands->full_cmd);

			if (!is_empty(piped_commands->full_cmd)) {
				commands->cmd_lst[(*commands->cnt)++] = piped_commands;
			}
			s=i+1;
		}
		if (inp[i] == '\\') esc = !esc;
	}
	return commands;
}

Commands_s * parse(char *inp) {
	
	Commands_s *commands = (Commands_s*) malloc(sizeof(Commands_s));
	commands->cmd_lst = (Piped_s**) malloc (MAX_BUFFER_CMDS*sizeof(Piped_s*));
	commands->cnt = (int *) malloc (sizeof(int));
	commands = get_commands(commands, inp);

	return commands;
}
