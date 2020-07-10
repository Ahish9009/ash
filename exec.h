#include<stdio.h>
#include<stdlib.h>

#include"utils.h"

#ifndef __EXEC_1
#define __EXEC_1

#define N_BUILTIN_COMMANDS 8

int launch_process(Cmd_s cmd);
void exec_piped(Commands_s *commands);


#endif
