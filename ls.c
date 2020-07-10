#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

#include"utils.h"
#include"sort.h"

char * ls_parse(Cmd_s *cmd, bool *flag_l, bool *flag_a) {

	char **argv = cmd->argv;

	*flag_l = 0; *flag_a = 0;
	char *dir_path = (char *) malloc (sizeof(char) * MAX_INPUT_SIZE); 
	for (int i = 1; i < cmd->argc; i++) {

		if (argv[i][0] == '-') {
			if (strchr(argv[i], 'l')) *flag_l = 1;
			if (strchr(argv[i], 'a')) *flag_a = 1;
		}
		else {
			if (argv[i][0] == '.' || argv[i][0] == '~' || argv[i][0] == '/') dir_path = argv[i]; 
			else dir_path = strcat(dir_path, argv[i]);
		}
	}

	if (!strlen(dir_path)) dir_path = "./";

	if (dir_path[strlen(dir_path)-1] != '/') strcat(dir_path, "/");
	return dir_path;
}

char * get_details(struct dirent *curr_file, char *dir_path) {

	char *temp = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
	temp[0] = 0;
	strcpy(temp, dir_path);
	struct stat file_details;
	stat(strcat(temp, curr_file->d_name), &file_details);

	/*generate details*/
	char *perms = (char *) malloc(sizeof(char) * 15);
	perms[0] = '-'; perms[11] = 0;
	if (S_ISDIR(file_details.st_mode)) perms[0] = 'd'; if (S_ISSOCK(file_details.st_mode)) perms[0] = 's';
	if (S_ISCHR(file_details.st_mode)) perms[0] = 'c'; if (S_ISLNK(file_details.st_mode)) perms[0] = 'l';

	int perm_vals[] = {
		S_IRUSR, S_IWUSR, S_IXUSR, 
		S_IRGRP, S_IWGRP, S_IXGRP, 
		S_IROTH, S_IWOTH, S_IXOTH
	}; 

	for (int i = 0; i < 9; i++) perms[i+1] = (file_details.st_mode & perm_vals[i]) ? "rwx"[i%3] : '-';  
	return perms;
}

void ls(Cmd_s *cmd) {

	bool flag_l, flag_a;
	char *dir_path = ls_parse(cmd, &flag_l, &flag_a);

	DIR *currDir = opendir(dir_path);
	struct dirent *curr_file = readdir(currDir);

	int n_items = 0;
	while (curr_file) {
		n_items++;
		curr_file = readdir(currDir);
	}
	closedir(currDir);

	currDir = opendir(dir_path);
	curr_file = readdir(currDir);

	char **dets = (char **) malloc ((n_items+2) * sizeof(char *));
	char **file_names = (char **) malloc ((n_items+2) * sizeof(char *));

	int i = 0;
	while (curr_file) {

		if (curr_file->d_name[0] == '.' && !flag_a) {
			curr_file = readdir(currDir);
			continue;
		}	
		if (flag_l) {
			char *perms = get_details(curr_file, dir_path);
			char *new = (char *) malloc (sizeof(char) * (strlen(perms) + strlen(curr_file->d_name) + 5));

			char *ext = "\n";
			if (perms[0] == 'd') ext = "/\n";
			else if (perms[3] == 'x') ext = "*\n";

			sprintf(new, "%s %s%s", perms, curr_file->d_name, ext);
			dets[i] = new;
			free(perms);
		}
		else {
			char *new = (char *) malloc (sizeof(char) * (strlen(curr_file->d_name)));
			sprintf(new, "%s\n", curr_file->d_name);
			dets[i] = new;
		}
		char *name = (char *) malloc (sizeof(char) * (strlen(curr_file->d_name)));
		name = curr_file->d_name;
		file_names[i++] = name;
		curr_file = readdir(currDir);
	}

	sort(dets, file_names);

	for (int i = 0; i < n_items; i++) {
		if (dets[i]) fprintf(stdout, "%s", dets[i]);
	}

	// freeing
	free(dets);
	free(file_names);
}
