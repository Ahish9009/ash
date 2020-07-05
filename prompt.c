#include<stdio.h>
#include"utils.h"

char * get_prompt() {
	
	char * prompt = (char *) malloc (MAX_PROMPT_LEN*sizeof(char));

	char *prefix = "[ash]";
		sprintf(prompt, YELLOW "%s" CLR_RST " %s@%s" BLUE ":%s" RED " $ " CLR_RST, prefix, user, user, path);

	return prompt;
}
