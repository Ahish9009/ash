#include<string.h>
#include<stdio.h>

#include"utils.h"

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
void display_hist() {

	for (int i = 0; i < hist.n; i++) {
		fprintf(stdout, "%d %s\n", i, hist.hist_arr[i]);
	}
}
