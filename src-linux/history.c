#include<string.h>
#include<stdio.h>

#include"utils.h"

bool validate_hist(Cmd_s *cmd) {
	if (cmd->argc > 2) {
		fprintf(stderr, "Usage: history <no. of commands>\n");
		return 1;
	}
	return 0;
}

void insert_hist(char *inp) {

	if (MAX_HIST_SIZE == 0) return;

	if (hist.n == MAX_HIST_SIZE && MAX_HIST_SIZE > 1) {
		for (int i = 1; i < hist.n; i++) {
			strcpy(hist.hist_arr[i-1], hist.hist_arr[i]);
		}
	}
	else {
		hist.n++;
	}
	strcpy(hist.hist_arr[hist.n - 1], inp);
}
void display_hist(Cmd_s *cmd) {
	
	if (validate_hist(cmd)) return;

	int i = 0;
	if (cmd->argc == 2) {
		int n = atoi(cmd->argv[1]);
		i = (hist.n - n >= 0) ? hist.n - n : 0;
	}

	while (i < hist.n) {
		fprintf(stdout, "%d %s\n", i, hist.hist_arr[i]);
		i++;
	}
}
