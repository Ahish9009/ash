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
#include"signals.h"
#include"processes.h"

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
	_STDIN = STDIN_FILENO;
	_STDOUT = STDOUT_FILENO;

	bg_procs = (Process_node *) malloc (sizeof(Process_node));
	bg_procs->root = 1;
	bg_procs->next = 0;

	signal (SIGINT, SIG_IGN);
	/*signal (SIGQUIT, SIG_IGN);*/
	signal (SIGTSTP, SIG_IGN);
	/*signal (SIGTTIN, SIG_IGN);*/
	/*signal (SIGTTOU, SIG_IGN);*/
	/*signal (SIGCHLD, SIG_IGN);*/

	shell_pid = getpid();
	int shell_term = STDIN_FILENO;

	if (setpgid (shell_pid, shell_pid) < 0) {
		perror ("ash: Couldn't put the shell in its own process group");
		exit (1);
        }
	tcsetpgrp (shell_term, shell_pid);

	// signals
	signal(SIGCHLD, bg_exit);
	/*signal(SIGINT, SIG_IGN);*/
	/*signal(SIGTSTP, SIG_IGN);*/
	/*signal(SIGINT, ctrl_c);*/
	/*signal(SIGTSTP, ctrl_z);*/

}

void repl() {

	while(1) {
		char *prompt = get_prompt();
		fprintf(stdout, "%s", prompt);

		char *inp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		get_input(inp);

		inp[strlen(inp)-1] = 0;
		if (!strcmp(inp, "exit")) return;


		Commands_s * commands = parse(inp);

		if (DEBUG) {
			for (int i = 0; i < *commands->cnt; i++) {
				fprintf(stderr, "full cmd: %s\n", commands->cmd_lst[i]->full_cmd);
				for (int j = 0; j < *(commands->cmd_lst[i]->cnt); j++) {
					fprintf(stderr, "Px: %s\n",commands->cmd_lst[i]->cmd_lst[j]->full_cmd);
				}
			}
		}

		exec_piped(commands);

		/*free(commands); //leaking memory, fix*/
		/*free(inp);*/
	}
}
