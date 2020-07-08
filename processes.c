#include<stdio.h>
#include"utils.h"

void insert(Process_node *node) {
	Process_node *last = bg_procs;
	while (last->next) last = last->next;
	last->next = node;
}

bool find(pid_t pid) {
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next; //first node is always root
		if (last->pid == pid) return 1;
	}
	return 0;
}
void display() {
	Process_node *last = bg_procs;
	while (last->next) {
		last = last->next;
		printf("P: %d\n", last->pid);
	}
}
