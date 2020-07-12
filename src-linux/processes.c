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

bool any_bg_process() {
	
	Process_node *last = bg_procs;
	Process_node *past = last;
	while (last->next) {
		past = last;
		last = last->next;

		char *proc_file = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));
		sprintf(proc_file, "/proc/%d/stat", last->pid);
		int ret = open(proc_file, O_RDONLY);
		if (ret <= 0) {
			pid_t del_pid = last->pid;
			last = past;
			delete_proc(del_pid);
		}
		if (last->bg && ret > 0) return 1;
	}
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

void display() {
	Process_node *last = bg_procs;
	int i = 1;
	while (last->next) {
		last = last->next;

		char *buf = (char *) malloc (MAX_INPUT_SIZE*sizeof(char));

		sprintf(buf, "/proc/%d/stat", last->pid);
		int fd = open(buf, O_RDONLY);

		if(fd < 0) {
			fprintf(stderr, "Couldn't find relevant files for pid %d\n", last->pid);
			perror("jobs");
			continue;
		}

		read(fd, buf, MAX_INPUT_SIZE);
		close(fd);
		char *status = "temp";


		printf("[%d] %s %s [%d]\n", i, status, last->name, last->pid);
		i++;
	}
	fflush(stdout);
}
