#include<stdio.h>
#include<libproc.h>
#include<ctype.h>

#include"utils.h"
#include"processes.h"

bool validate_pinfo(Cmd_s *cmd) {

	if (cmd->argc > 2) {
		fprintf(stderr, "Usage: pinfo <pid>\n");
		return 1;
	}
	return 0;
}

void pinfo(Cmd_s *cmd) {

	if (validate_pinfo(cmd)) return;

	int pid;
	if (cmd->argc == 1) pid = shell_pid;
	else pid = atoi(cmd->argv[1]);

	struct proc_taskallinfo info;
	int ret = proc_pidinfo(pid, PROC_PIDTASKALLINFO, 0, &info, sizeof(struct proc_taskallinfo));
	char *stat = "";
	int mem = info.ptinfo.pti_virtual_size;
	if (ret > 0) { 
		int s_no = info.pbsd.pbi_status;
		if (s_no == 1) stat = "idle"; 	
		else if (s_no == 2) stat = "running"; 	
		else if (s_no == 3) stat = "sleeping"; 	
		else if (s_no == 4) stat = "suspended";
		else if (s_no == 5) stat = "zombie";
		else stat = "unknown";
	}

	char proc_path[PROC_PIDPATHINFO_MAXSIZE];
	ret = proc_pidpath(pid, &proc_path, PROC_PIDPATHINFO_MAXSIZE);

	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "status: %s\n", stat);
	fprintf(stdout, "memory: %d\n", mem);
	fprintf(stdout, "path: %s\n", proc_path);


}
