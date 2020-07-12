#include"utils.h"

#ifndef __PROCESSES_1
#define __PROCESSES_1

void insert(Process_node *node);
bool find_bg(pid_t pid);
Process_node * get_bg_proc(pid_t pid);
Process_node * get_by_ind(int n);
Process_node * get_by_pid(pid_t pid);
void delete_proc(pid_t pid);
void display();
bool any_bg_process();

#endif
