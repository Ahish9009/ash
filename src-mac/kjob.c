#include<stdio.h>
#include <sys/types.h>
#include <signal.h>

#include"utils.h" 
#include"processes.h"

bool validate_kjob(Cmd_s *cmd) {
	if (cmd->argc < 3) return 1;
	return 0;
}

void kjob(Cmd_s *cmd) {

	if (validate_kjob(cmd)) {
		fprintf(stderr, "Usage: kjob <signal_number> [pid ...]\n");
		return;
	}

	int signal = atoi(cmd->argv[1]);

	for (int i = 2; i < cmd->argc; i++) {

		Process_node *curr = get_by_pid(atoi(cmd->argv[i]));

		if (!curr) {
			fprintf(stderr, "Process with pid %s doesn't exist\n", 
					cmd->argv[i]);
			continue;
		}
		if (kill(atoi(cmd->argv[i]), signal)) {
			fprintf(stderr, GREEN "Error sending signal to the process\n" CLR_RST);
		}
		else {
			fprintf(stdout, GREEN "Successfully sent signal to process with pid %s\n" CLR_RST, 
					cmd->argv[i]);
		}
	}
}
