#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>

#include"prompt.h"
#include"utils.h"
#include"parse.h"
#include"exec.h"
#include"signals.h"
#include"processes.h"
#include"history.h"

pid_t shell_pid;
char *user;
char *hostname;
char *home_path;
bool handle_up_arrow(char *inp) {
	int n_up = 0;
	for (int i = 0; inp[i]; i++) {
		if ((int)(inp[i]) == 27) n_up++;
	}

	if (n_up) {
		inp[0] = 0;
		strcpy(inp,hist.hist_arr[(hist.n - n_up) % MAX_HIST_SIZE]);
		show_prompt();
		fprintf(stdout, "%s", inp);
		fflush(stdout);
		return 1;
	}
	return 0;
}

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

void get_input(char *ptr) {
	fgets(ptr, MAX_INPUT_SIZE, stdin);
	while (open_quotes(ptr) && strlen(ptr) < MAX_INPUT_SIZE) {
		fprintf(stdout, "quote> ");
		char *temp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		fgets(temp, MAX_INPUT_SIZE-strlen(ptr), stdin);
		ptr[strlen(ptr)-1] = 0;
		strcat(ptr, temp);
		free(temp);
	}
	// fpurge only works on MacOS
	/*fpurge(stdin);*/
	fflush(stdin);
}

void init() {

	home_path = getenv("PWD");
	old_path = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	strcpy(old_path, home_path);
	user = getenv("USER");
	hostname = (char *) malloc (20*sizeof(char));
	if (gethostname(hostname, 20)) hostname = user;
	
	_STDIN = STDIN_FILENO;
	_STDOUT = STDOUT_FILENO;

	bg_procs = (Process_node *) malloc (sizeof(Process_node));
	bg_procs->root = 1;
	bg_procs->next = 0;

	signal (SIGTTIN, SIG_IGN);
	signal (SIGTTOU, SIG_IGN);

	shell_pid = getpid();
	int shell_term = STDIN_FILENO;

	if (setpgid (shell_pid, shell_pid) < 0) {
		perror ("ash: Couldn't put the shell in its own process group");
		exit (1);
        }
	tcsetpgrp (shell_term, shell_pid);

	FILE * hist_file = fopen(".ash_history", "rb");
	if (hist_file) {
		fread(&hist, sizeof(hist), 1, hist_file);	
		fclose(hist_file);
	}
	else hist.n = 0;

	// signals
	signal(SIGCHLD, bg_exit);
	signal(SIGINT, ctrl_c);
	signal(SIGTSTP, ctrl_z);

	char *init_msg = "\
                                                                                  \n\
"YELLOW"               AAA                                       HHHHHHHHH     HHHHHHHHH     \n\
"YELLOW"              A:::A           "RED"        SSSSSSSSSSSSSSS   "YELLOW" H:::::::H     H:::::::H     \n\
"YELLOW"             A:::::A          "RED"      SS:::::::::::::::S  "YELLOW" H:::::::H     H:::::::H     \n\
"YELLOW"            A:::::::A         "RED"     S:::::SSSSSS::::::S  "YELLOW" HH::::::H     H::::::HH     \n\
"YELLOW"           A:::::::::A        "RED"     S:::::S     SSSSSSS  "YELLOW"   H:::::H     H:::::H       \n\
"YELLOW"          A:::::A:::::A       "RED"     S:::::S              "YELLOW"   H:::::H     H:::::H       \n\
"YELLOW"         A:::::A A:::::A      "RED"      S::::SSSS           "YELLOW"   H::::::HHHHH::::::H       \n\
"YELLOW"        A:::::A   A:::::A     "RED"   ======================= " YELLOW "  H:::::::::::::::::H       \n\
"YELLOW"       A:::::A     A:::::A    "RED"   ======================= " YELLOW "  H:::::::::::::::::H       \n\
"YELLOW"      A:::::AAAAAAAAA:::::A   "RED"            SSSSSS::::S   "YELLOW"   H::::::HHHHH::::::H       \n\
"YELLOW"     A:::::::::::::::::::::A  "RED"                 S:::::S  "YELLOW"   H:::::H     H:::::H       \n\
"YELLOW"    A:::::AAAAAAAAAAAAA:::::A "RED"     SSSSSSS     S:::::S  "YELLOW"   H:::::H     H:::::H       \n\
"YELLOW"   A:::::A             A:::::A "RED"    s::::::ssssss:::::s  "YELLOW" HH::::::H     H::::::HH     \n\
"YELLOW"  A:::::A               A:::::A "RED"   S:::::::::::::::SS  "YELLOW"  h:::::::h     h:::::::h     \n\
"YELLOW" A:::::A                 A:::::A "RED"   SSSSSSSSSSSSSSS   "YELLOW"   H:::::::H     H:::::::H     \n\
"YELLOW"AAAAAAA                   AAAAAAA                        HHHHHHHHH     HHHHHHHHH     \n\
			  ";
	fprintf(stdout, "\e[1;1H\e[2J" RED "%s" CLR_RST "\nWelcome to Ahish's shell: as̶h!\nUse 'help' for more information\n\n", init_msg); 
}

void repl() {

	while(1) {

		show_prompt();

		char *inp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		get_input(inp);

		inp[strlen(inp)-1] = 0;
		if (!strcmp(inp, "exit")) return;

		if (handle_up_arrow(inp)) {
			char *temp = (char *) malloc((MAX_INPUT_SIZE - strlen(inp)+1)*sizeof(char));
			get_input(temp);
			inp = strncat(inp, temp, MAX_INPUT_SIZE);
			inp[strlen(inp)-1] = 0;
		}

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
		if (strlen(inp)) insert_hist(inp);

		free(commands); //leaking memory, fix
		free(inp);
	}
}

void exit_shell() {

	FILE * hist_file = fopen(".ash_history", "wb");
	if (hist_file) {
		if (fwrite(&hist, sizeof(hist), 1, hist_file) != 1) {
			fprintf(stderr, "\nash: Failed to save history\n");
		}
		fclose(hist_file);
	}
	else fprintf(stderr, "\nash: Failed to save history\n");


}
