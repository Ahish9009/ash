#include<stdio.h>
#include<libproc.h>
#include<ctype.h>

#include"utils.h"
#include"processes.h"

void pinfo(Cmd_s *cmd) {

	Process_node *curr = get_by_pid(atoi(cmd->argv[1]));
	if (!curr) {
		fprintf(stderr, "Process with pid %s wasn't found\n", cmd->argv[1]);
		return;
	}


	struct proc_taskallinfo info;
	int ret = proc_pidinfo(atoi(cmd->argv[1]), PROC_PIDTASKALLINFO, 0, &info, sizeof(struct proc_taskallinfo));
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
	ret = proc_pidpath(atoi(cmd->argv[1]), &proc_path, PROC_PIDPATHINFO_MAXSIZE);


	fprintf(stdout, "pid: %s\n", cmd->argv[1]);
	fprintf(stdout, "status: %s\n", stat);
	fprintf(stdout, "memory: %d\n", mem);
	fprintf(stdout, "path: %s\n", proc_path);


}
