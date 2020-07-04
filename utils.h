#include<stdlib.h>
#include<ctype.h>

#ifndef __UTILS_1
#define __UTILS_1

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CLR_RST "\x1b[0m"

#define MAX_INPUT_SIZE  100
#define MAX_BUFFER_CMDS 20
#define MAX_TOKENS      100

typedef struct {
	char *full_cmd;
	int argc;
	char **argv;
} Cmd_s;
typedef struct {
	int cnt;
	Cmd_s **cmd_lst;
		
} Commands_s;

# endif
