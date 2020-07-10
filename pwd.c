#include<stdio.h>
#include<unistd.h>

#include"utils.h"

void pwd(Cmd_s *cmd) {

	char *buf = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
	if (!getcwd(buf, MAX_INPUT_SIZE)) {
		perror("ash: pwd");
		return;
	}
	fprintf(stdout, "%s\n", buf);
	free(buf);

}

