#include<stdio.h>
#include<unistd.h>
#include"string.h"

#include"utils.h"
#include"processes.h"


char * get_tilda(char *path) {
	
	char * temp = (char *) malloc(strlen(path)*sizeof(char));
	strcpy(temp, path);

	int len = strlen(home_path);
	if (strlen(path) >= len) {
		temp[strlen(home_path)] = 0;
		if (!strcmp(temp, home_path)) {
			path += strlen(home_path)-1;
			path[0] = '~';

			free(temp);
			return path;
		}
	}
	free(temp);
	return path;

}

void show_prompt() {
	
	char * prompt = (char *) malloc (MAX_PROMPT_LEN*sizeof(char));
	char *bg_proc_symb = (any_bg_process()) ? "*" : "";

	char * path = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	if (!getcwd(path, MAX_INPUT_SIZE)) path = "~";
	path = get_tilda(path);

	char *prefix = "[as̶h]";
	sprintf(prompt, YELLOW "%s%s" CLR_RST " %s@%s" GREEN ":%s" YELLOW " $ " CLR_RST, prefix, bg_proc_symb, user, hostname, path);

	fprintf(stdout, "%s", prompt);
	free(prompt);

}
