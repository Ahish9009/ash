#include<libproc.h>
#include<stdio.h>

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
	int flag = 0;
	while (last->next) {
		past = last;
		last = last->next;

		struct proc_taskallinfo info;
		int ret = proc_pidinfo(last->pid, PROC_PIDTASKALLINFO, 0, &info, sizeof(struct proc_taskallinfo));
		if (ret <= 0) {
			pid_t del_pid = last->pid;
			last = past;
			delete_proc(del_pid);
		}
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

		struct proc_taskallinfo info;

		int ret = proc_pidinfo(last->pid, PROC_PIDTASKALLINFO, 0, &info, sizeof(struct proc_taskallinfo));
		if (ret > 0) { 

			int s_no = info.pbsd.pbi_status;
			char *stat;
			if (s_no == 1) stat = "idle"; 	
			else if (s_no == 2) stat = "running"; 	
			else if (s_no == 3) stat = "sleeping"; 	
			else if (s_no == 4) stat = "suspended";
			else if (s_no == 5) stat = "zombie";
			else stat = "unknown";
		fprintf(stdout, "[%d] %d %s %s\n", i++, last->pid, stat,last->name);
		   }	
	}
	fflush(stdout);
}
