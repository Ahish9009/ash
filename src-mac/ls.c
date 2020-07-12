#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>

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

void print_l(struct dirent *curr_file, char *dir_path) {

	char *temp = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
	temp[0] = 0;
	strcpy(temp, dir_path);
	struct stat f_dets;
	if (lstat(strcat(temp, curr_file->d_name), &f_dets) == -1) {
		perror("ash: ls:");
		return;
	}

	char *mode = (char *) malloc (11*sizeof(char));
	mode[10] = 0;
	switch (f_dets.st_mode & S_IFMT) {
		case S_IFBLK:  mode[0] = 'b'; break;
		case S_IFCHR:  mode[0] = 'c'; break;
		case S_IFDIR:  mode[0] = 'd'; break;
		case S_IFIFO:  mode[0] = 'p'; break;
		case S_IFLNK:  mode[0] = 'l'; break;
		case S_IFREG:  mode[0] = '-'; break;
		case S_IFSOCK: mode[0] = 's'; break;
		default:       mode[0] = '?'; break;
	}
	int perms[9] = {
		S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH 
	};
	for (int i = 1; i < 10; i++) mode[i] = perms[i-1] & f_dets.st_mode;
	for (int i = 1; i < 10; i+=3) mode[i] = (mode[i]) ? 'r' : '-';
	for (int i = 2; i < 10; i+=3) mode[i] = (mode[i]) ? 'w' : '-';
	for (int i = 3; i < 10; i+=3) mode[i] = (mode[i]) ? 'x' : '-';

	char *time = ctime(&f_dets.st_mtime)+4;
	time[12] = 0;
	char *name_color = CLR_RST;
	char name_ext = ' ';
	if (mode[0] == 'd') {
		name_color = BLUE;
		name_ext = '/';
	}
	else if (mode[3] == 'x') {
		name_color = RED;
		name_ext = '*';
	}


	fprintf(stdout, YELLOW "%s " CLR_RST "%2ld %s %s %6lldB %s " CLR_RST "%s%s" CLR_RST"%c\n", 
			mode, 
			(long) f_dets.st_nlink, 
			getpwuid(f_dets.st_uid)->pw_name,
                	getgrgid(f_dets.st_gid)->gr_name,
			f_dets.st_size,
			time,
			name_color,
			curr_file->d_name,
			name_ext
	);
	free(temp);
	free(mode);
}

int no_hidden (const struct dirent *dir) {
	return (dir->d_name[0] == '.') ? 0 : 1;
}

long long get_block_size(struct dirent *curr_file, char *dir_path) {

	char *temp = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
	temp[0] = 0;
	strcpy(temp, dir_path);
	struct stat f_dets;
	if (lstat(strcat(temp, curr_file->d_name), &f_dets) == -1) {
		perror("ash: ls:");
		return 0;
	}

	free(temp);
	return f_dets.st_blocks;
}

void ls(Cmd_s *cmd) {

	bool flag_l, flag_a;
	char *dir_path = ls_parse(cmd, &flag_l, &flag_a);

	struct dirent **curr_file;
	int n;

	if (flag_a) n = scandir(dir_path, &curr_file, NULL, alphasort);
	else n = scandir(dir_path, &curr_file, no_hidden, alphasort);

	if (n == -1) {
		perror("ash: ls");
		return;
	}

	if (flag_l) {
		long long int total = 0;
		for (int i = 0; i < n; i++) total += get_block_size(curr_file[i], dir_path);
		fprintf(stdout, "total %lld\n", total);
	}

	for (int i = 0; i < n; i++) {
		if (flag_l) print_l(curr_file[i], dir_path);
		else fprintf(stdout, "%s\n", curr_file[i]->d_name);
		free(curr_file[i]);
	}
	free(curr_file);
}
