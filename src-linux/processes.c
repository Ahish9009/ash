#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include"utils.h"
#include"processes.h"

void insert(Process_node *node) {

	Process_node *last = bg_procs;
	while (last->next) last = last->next;
	last->next = node;
}

bool find_bg(pid_t pid) {
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next; //first node is always root
		if (last->pid == pid && last->bg) return 1;
	}
	return 0;
}

Process_node *get_bg_proc(pid_t pid) {
	if (!find_bg(pid)) return 0;
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next; //first node is always root
		if (last->pid == pid && last->bg) return last;

	}
	return 0;

}

Process_node *get_by_pid(pid_t pid) {
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next; //first node is always root
		if (last->pid == pid) return last;
	}
	return 0;

}

void delete_proc(pid_t pid) {

	Process_node *last = bg_procs;
	while (last->next) {

		if (last->next->pid == pid) {
			Process_node *temp = last->next;
			last->next = last->next->next;
			free(temp);
			return;
		}
		last = last->next;
	}
}

bool any_bg_process() {
	
	Process_node *last = bg_procs;
	Process_node *past = last;
	int flag = 0;
	while (last->next) {
		past = last;
		last = last->next;

		char *proc_file = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
		sprintf(proc_file, "/proc/%d/stat", last->pid);
		int ret = open(proc_file, O_RDONLY);


		if (ret < 0) {

			pid_t del_pid = last->pid;
			last = past;
			delete_proc(del_pid);
		}
		else close(ret);
		if (last->bg && ret > 0) flag = 1;
	}
	if (flag) return 1;
	return 0;
}

Process_node *get_by_ind(int n) {
	int i = 0;
	Process_node *last = bg_procs;
	while (last->next && i != n) {
		last = last->next;
		i++;
	}
	if (i != n) return 0;
	else return last;
}


void display() {
	Process_node *last = bg_procs;
	int ind = 1;
	while (last->next) {
		last = last->next;

		char *proc_fpath = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));

		sprintf(proc_fpath, "/proc/%d/stat", last->pid);
		FILE *fd = fopen(proc_fpath, "r");

		if(fd < 0) continue;
		int *i = (int *) malloc (sizeof(int));	
		char *ign = (char *) malloc(MAX_INPUT_SIZE*sizeof(char));
		char status;

		fscanf(fd, "%d %s %c", i, ign, &status);

		fclose(fd);
		free(i);
		free(ign);

		char *status_desc;
		if (status == 'R') status_desc = "running";
		else if (status == 'T' || status == 't') status_desc = "stopped";
		else if (status == 'S') status_desc = "sleeping";
		else if (status == 'D') status_desc = "waiting";
		else if (status == 'Z') status_desc = "zombie";
		else status_desc = "other";

		printf("[%d] %d %s %s\n", ind, last->pid, status_desc, last->name);
		ind++;
	}
	fflush(stdout);
}
