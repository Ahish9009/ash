#include<stdio.h>
#include<stdlib.h>

#include"utils.h"

#ifndef __EXEC_H_
#define __EXEC_H_

#define N_BUILTIN_COMMANDS 15

int launch_process(Cmd_s cmd);
void exec_piped(Commands_s *commands);


#endif
