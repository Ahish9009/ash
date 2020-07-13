#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

#ifndef __UTILS_H_
#define __UTILS_H_

#define DEBUG 0

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CLR_RST "\x1b[0m"

#define MAX_INPUT_SIZE  100
#define MAX_BUFFER_CMDS 20
#define MAX_TOKENS      100
#define MAX_PROMPT_LEN  150
#define MAX_HIST_SIZE   25

typedef struct Command_info {
	char *f_in;
	char *f_out;
	int a;
	bool in_bg;
	char *full_cmd;
	int argc;
	char **argv;
} Cmd_s;
typedef struct Piped_commands {
	char *full_cmd;
	int *cnt;
	Cmd_s **cmd_lst;
} Piped_s;
typedef struct Commands_s {
	int *cnt;
	Piped_s **cmd_lst;
} Commands_s;

typedef struct Process_node {
	pid_t pid;
	char *name;
	bool root;
	bool bg;
	struct Process_node *next;
} Process_node;

typedef struct History_s {
	int n;
	char hist_arr[MAX_HIST_SIZE][MAX_INPUT_SIZE];
} History_s;

int shell_term;
pid_t shell_pid;
char *user;
char *hostname;
char *home_path;
char *old_path;
int _STDIN, _STDOUT;
History_s hist;

Process_node *all_procs;
Process_node *bg_procs;

void init();
void repl();
void exit_shell();
char * strip(char *x);
bool is_empty(char *x);

# endif
