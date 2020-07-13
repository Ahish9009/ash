#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<time.h>
#include<sys/wait.h>

#include"utils.h"
#include"parse.h"
#include"exec.h"
#include"prompt.h"

bool validate_cronjob(Cmd_s *cmd) {

	if (cmd->argc != 7) {
		fprintf(stderr, "Usage: cronjob -c <cmd> -t <interval> -p <period>\n");
		return 1;
	}
	
	return 0;
}

void exec_cronjob(char *cmd_inp, int interval, int t) {
	
	Commands_s * commands = parse(cmd_inp);
	time_t start_time = time(0);
	time_t end_time = start_time + t;

	while (time(0) < end_time) {
		
		while (time(0) < start_time + interval) {
			continue;
		}
		start_time = time(0);
		exec_piped(commands);
		show_prompt();
		fflush(stdout);
	}
	return;
}

void cronjob(Cmd_s *cmd) {

	if (validate_cronjob(cmd)) return;
	
	char *cmd_inp = (char *) malloc (MAX_INPUT_SIZE*sizeof(cmd));
	int interval, t;

	for (int i = 0; i < cmd->argc; i++) {
		if (!strcmp(cmd->argv[i], "-c")) {
			cmd_inp = cmd->argv[i+1];
		}
		else if (!strcmp(cmd->argv[i], "-t")) {
			interval = atoi(cmd->argv[i+1]);
		}			
		else if (!strcmp(cmd->argv[i], "-p")) {
			t = atoi(cmd->argv[i+1]);
		}			
	}

	if (t < 0 || interval < 0 || !cmd_inp) return; 
	
	pid_t pid = fork();
	if (pid == 0) {
		exec_cronjob(cmd_inp, interval, t);
		fprintf(stdout, GREEN "Cronjob completed\n" CLR_RST);
		show_prompt();
		exit(EXIT_SUCCESS);
	}

}
