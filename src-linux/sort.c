#include<stdio.h>
#include<string.h>

void sort(char **arr, char **cmp_arr) {
	char *tmp, *tmp2;
	for(int i = 0; arr[i]; i++) {
		for(int j = 0; arr[j]; j++) {
			if(strcmp(cmp_arr[i], cmp_arr[j]) < 0) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;

				tmp2 = cmp_arr[i];
				cmp_arr[i] = cmp_arr[j];
				cmp_arr[j] = tmp2;
			}
		}
	}
}
