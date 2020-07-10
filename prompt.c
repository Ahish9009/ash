#include<stdio.h>
#include"utils.h"
#include"processes.h"

char * get_prompt() {
	
	char * prompt = (char *) malloc (MAX_PROMPT_LEN*sizeof(char));
	char *bg_proc_symb = (any_bg_process()) ? "*" : "";

	char *prefix = "[as̶h]";
	sprintf(prompt, YELLOW "%s%s" CLR_RST " %s@%s" GREEN ":%s" YELLOW " $ " CLR_RST, prefix, bg_proc_symb, user, hostname, path);

	return prompt;
}
