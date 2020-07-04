#include<stdio.h>
#include"utils.h"

char * get_prompt() {
	
	char * prompt = (char *) malloc (MAX_PROMPT_LEN*sizeof(char));

	char *prefix = "[ash]";
	sprintf(prompt, "%s %s@%s:%s $ ", prefix, user, user, path);

	return prompt;
}
