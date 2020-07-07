#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>

#include"prompt.h"
#include"utils.h"
#include"parse.h"
#include"exec.h"

pid_t shell_pid;
char *user;
char *home_path;
char *path;

char * strip(char *x) {

	while (*x == ' ') x++;

	int len = strlen(x)-1;
	while (len > 0 && x[len]==' ') len--;
	x[len+1]=0;

	return x;
}

bool is_empty(char *x) {
	if (!x) return 1;
	if (!strlen(x)) return 1;
	for (int i = 0; i < strlen(x); i++) {
		if (x[i] != ' ') return 0;
	}
	return 1;
}

bool open_quotes(char *inp) {

	bool esc=0, in_sq=0, in_dq=0;
	for (int i=0; inp[i] != 0; i++) {
		if (!esc && inp[i] == '\'') in_sq=!in_sq;
		if (!(esc | in_sq) && inp[i] == '\"') in_dq=!in_dq;
		if (esc || inp[i] == '\\') esc=!esc;
	}
	if (in_sq | in_dq) return 1;
	return 0;
}

void get_input(char *inp) {
	fgets(inp, MAX_INPUT_SIZE, stdin);
	while (open_quotes(inp) && strlen(inp) < MAX_INPUT_SIZE) {
		fprintf(stdout, "quote> ");
		char *temp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		fgets(temp, MAX_INPUT_SIZE-strlen(inp), stdin);
		inp[strlen(inp)-1] = 0;
		strcat(inp, temp);
		free(temp);
	}
	fpurge(stdin);
}

void init() {

	home_path = getenv("PWD");
	user = getenv("USER");
	path = "~";
	shell_pid = getpid();
	
}

void repl() {

	while(1) {
		char *prompt = get_prompt();
		fprintf(stdout, "%s", prompt);

		char *inp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		get_input(inp);

		Commands_s * commands = parse(inp);

		if (DEBUG) {
			for (int i = 0; i < commands->cnt; i++) {
				fprintf(stderr, "full cmd: %s\n", commands->cmd_lst[i]->full_cmd);
				for (int j = 0; j < *(commands->cmd_lst[i]->argc); j++) {
					fprintf(stderr, "%s|\n",commands->cmd_lst[i]->argv[j]);
				}
			}
		}

		for (int i = 0; i < commands->cnt; i++) {
			launch_process(commands->cmd_lst[i]->argv);
		}

		free(commands); //leaking memory, fix
		free(inp);
	}
}
