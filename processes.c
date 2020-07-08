#include<stdio.h>
#include"utils.h"

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

Process_node *get_bg(pid_t pid) {
	if (!find_bg(pid)) return 0;
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next; //first node is always root
		if (last->pid == pid && last->bg) return last;
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

void display() {
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next;
		printf("P: %d\n", last->pid);
	}
}
