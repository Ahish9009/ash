#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>

#include"prompt.h"
#include"utils.h"
#include"parse.h"

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
	fprintf(stderr, "%lu\n", strlen(x));
	if (!strlen(x)) return 1;
	for (int i = 0; i < strlen(x); i++) {
		fprintf(stderr, "%c\n", x[i]);
		if (x[i] != ' ') return 0;
	}
	return 1;
}

void init() {

	home_path = getenv("PWD");
	user = getenv("USER");
	shell_pid = getpid();
	path = "~";
	
}

void repl() {

	while(1) {
		char *prompt = get_prompt();
		fprintf(stdout, "%s", prompt);

		char *inp = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		fgets(inp, MAX_INPUT_SIZE, stdin);

		parse(inp);
	}

}
