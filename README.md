# as̶h
Custom shell in low level C for linux & Mac.

# Contents

|S. No| Topic|
|:---:|:----:|
|1    | [Usage](#usage) |
|2    | [Features](#features) |
|3    | [Built-In Commands](#built-in-commands) |
|4    | [Naming of the Shell](#naming) |
|5    | [To-Do](#to-do) |
|6    | [Author(s)](#authors) |

# Usage

- ##### Clone the repo
  `git clone https://github.com/Ahish9009/ash/`
- ##### Navigate into it 
  `cd ash`
- ##### Generate the binary executable
  **on `Linux`**: `make linux` \
  **on `MacOS`**: `make mac`
- ##### Execute 
  `./ash`

# Features

- Set of self-written custom built-in commands
  - Self written and customized
  - Run within the shell's process itself
  - The list of built-in commands can be found [here](#Built-In-Commands)
- Supports semi-colon separated commands
  - Eg. `ls ; cd ..; echo`
- Supports multiple piping
  - Eg. `ls | cat | tail -3`
- Supports input & output redirection
  - Eg. `cat < inp > out`
- Allows job control/process management
  - Jobs can be run in the foreground or background
  - Background jobs can be brought to the foreground and vice versa
  - Process exit status is displayed on termination of a background job
- Stores command history
- Handles/traps signals
  - `CTRL-Z` sends the job(s) in the foreground to the background
  - `CTRL-C` terminates the current foreground job
- Previous commands can be recalled using the `up arrow key`
  - The *n<sup>th</sup>* command can be recalled by pressing the `up arrow key` *n* times and hitting `enter`


# Built In Commands

The following commands are built into the shell:

### ls
###### Usage: 
`
ls -[al] [path/to/dir]
`
###### Description
- Lists files in the specified directory 
- Lists files of the current directory if no path is specified
###### Options
- `-l` : list in long format with more details
- `-a` : display hidden files *(those starting with '.')*
#

### cd
###### Usage: 
`
cd [path/to/dir]
`
###### Description
- Changes working directory to the path specified
- Accepts both *absolute* and *relative* paths
###### Options
- `cd -` : switches to the *previous* working directory
- `cd` : switches to the *root* directory
#

### pwd
###### Usage:
`
pwd
`
###### Description
- returns the name of the current working directory 
#

### echo
###### Usage:
`
echo -[n] [string ...]
`
###### Description
- write arguments to the standard output
###### Options
- `-n` : does not print the trailing newline character
#

### jobs
###### Usage:
`
jobs
`
###### Description
- display status of jobs in the current session
#

### kjob
###### Usage:
`
kjob <signal number> [pid ...]
`
###### Description
- send the specified signal to the specified processes
- Multiple pids can be passed
#

### history
###### Usage:
`
history [n]
`
###### Description
- displays the history of commands
- passing a number *n* as argument displays the last *n* entries
#

### fg
###### Usage:
`
fg [job id]
`
###### Description
- runs the job specified by <*job id*> in the foreground 
- <*job id*> can be found using `jobs`
#

### bg
###### Usage:
`
bg [job id]
`
###### Description
- run the job specified by <*job id*> in the background
- <*job id*> can be found using `jobs`
#

### overkill
###### Usage:
`
overkill
`
###### Description
- kill all background processes
#

### pinfo
###### Usage:
`
pinfo [pid]
`
###### Description
- shows information on the process specified by the pid
- shows shell process information if no argument is passed
#

### set_env
###### Usage:
`
set_env [name] [value]
`
###### Description
- sets the environment variable ***name*** to have the specified ***value***
#
 
### unset_env
###### Usage:
`
unset_env [name] 
`
###### Description
- unsets the environment variable ***name*** 
#

### cronjob
###### Usage:
`
cronjob -c [command] -t [time] -p [period] 
`
###### Description
- executes ***command*** every ***time*** seconds for ***period*** duration
#

# Naming

The shell is named using the "**\<initial\>SH**" convention \
The **~~s~~** in a~~s~~h is to emphasize the absence of an ***'s'*** before the first ***'h'*** in **Ahish** :P


# To-Do

- [x] ';' separated commands
- [x] Piping (multiple)
- [x] Redirection
- [x] fg/bg
- [x] Built-in commands
  - [x] echo
  - [x] ls
  - [x] cd
  - [x] pwd
  
# Author(s)
  
[Ahish Deshpande](https://ahish9009.github.io)
  
