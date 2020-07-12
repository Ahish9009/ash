#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"utils.h"

int fd_in, fd_out;

void set_redirect(Cmd_s cmd) {

	if (strcmp(cmd.f_in, "")) {
		_STDIN = dup(STDIN_FILENO);

		fd_in = open(cmd.f_in, O_RDONLY, 0644);
		if (fd_in < 0) perror("Redirection input error");
		else dup2(fd_in, STDIN_FILENO);
	}
	if (strcmp(cmd.f_out, "")) {
		_STDOUT = dup(STDOUT_FILENO);

		if (cmd.a) 
			fd_out = open(cmd.f_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else 
			fd_out = open(cmd.f_out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		
		if (fd_out < 0) perror("Redirection output error");
		else dup2(fd_out, STDOUT_FILENO);
	}
}

void unset_redirect(Cmd_s cmd) {

	if (strcmp(cmd.f_in, "")) {
		dup2(_STDIN, STDIN_FILENO);
		close(_STDIN); close(fd_in);
	}
	if (strcmp(cmd.f_out, "")) {
		dup2(_STDOUT, STDOUT_FILENO);
		close(_STDOUT); close(fd_out);	
	}
}
