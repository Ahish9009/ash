# as̶h
Custom shell in low level C for Linux & Mac.

![shell ss](img/ss3.png)

# Contents

|S. No| Topic|
|:---:|:----:|
|1    | [Usage](#usage) |
|2    | [Features](#features) |
|3    | [Built-In Commands](#built-in-commands) |
|4    | [File Structure](#file-structure) |
|5    | [Naming of the Shell](#naming-of-the-shell) |
|6    | [To-Do](#to-do) |
|7    | [Author(s)](#authors) |

# Usage

- ##### Clone the repo
  `git clone https://github.com/Ahish9009/ash/`
- ##### Navigate into it 
  `cd ash`
- ##### Generate the binary executable
  **on `Linux`**: `make linux` \
  **on `MacOS`**: `make mac` or `make`
- ##### Execute 
  `./ash`
- ##### Clean 
  `make clean`

# Features

- Set of **self-written custom built-in commands**
  - Self written and customized
  - Run within the shell's process itself
  - The list of built-in commands can be found [here](#Built-In-Commands)
- Supports **semi-colon separated** commands
  - Eg. `ls ; cd ..; echo`
- Supports **multiple piping**
  - Eg. `ls | cat | tail -3`
- Supports **input & output redirection**
  - Eg. `cat < inp > out`
- Allows **job control/process management**
  - Jobs can be run in the foreground or background
  - Background jobs can be brought to the foreground and vice versa
  - Process exit status is displayed on termination of a background job
- Stores command **history**
- **Handles/traps signals**
  - `CTRL-Z` sends the job(s) in the foreground to the background
  - `CTRL-C` terminates the current foreground job
- Previous commands can be **recalled using the `up arrow key`**
  - The *n<sup>th</sup>* command can be recalled by pressing the `up arrow key` *n* times and hitting `enter`


# Built In Commands

The following self-written commands are built into the shell:

### ls <sub><sup>[[MacOS]](src-mac/ls.c)</sup></sub><sub><sup> [[Linux]](src-linux/ls.c)</sup></sub>
###### Usage 
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

### cd <sub><sup>[[MacOS]](src-mac/cd.c)</sup></sub><sub><sup> [[Linux]](src-linux/cd.c)</sup></sub>
###### Usage 
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

### pwd <sub><sup>[[MacOS]](src-mac/pwd.c)</sup></sub><sub><sup> [[Linux]](src-linux/pwd.c)</sup></sub>
###### Usage
`
pwd
`
###### Description
- returns the name of the current working directory 
#

### echo <sub><sup>[[MacOS]](src-mac/echo.c)</sup></sub><sub><sup> [[Linux]](src-linux/echo.c)</sup></sub>
###### Usage
`
echo -[n] [string ...]
`
###### Description
- write arguments to the standard output
###### Options
- `-n` : does not print the trailing newline character
#

### jobs <sub><sup>[[MacOS]](src-mac/jobs.c)</sup></sub><sub><sup> [[Linux]](src-linux/jobs.c)</sup></sub>
###### Usage
`
jobs
`
###### Description
- display status of jobs in the current session
#

### kjob <sub><sup>[[MacOS]](src-mac/kjob.c.c)</sup></sub><sub><sup> [[Linux]](src-linux/kjob.c.c)</sup></sub>
###### Usage
`
kjob <signal number> [pid ...]
`
###### Description
- send the specified signal to the specified processes
- Multiple pids can be passed
#

### history <sub><sup>[[MacOS]](src-mac/history.c)</sup></sub><sub><sup> [[Linux]](src-linux/history.c)</sup></sub>
###### Usage
`
history [n]
`
###### Description
- displays the history of commands
- passing a number *n* as argument displays the last *n* entries
#

### fg <sub><sup>[[MacOS]](src-mac/fg.c)</sup></sub><sub><sup> [[Linux]](src-linux/fg.c)</sup></sub>
###### Usage
`
fg [job id]
`
###### Description
- runs the job specified by <*job id*> in the foreground 
- <*job id*> can be found using `jobs`
#

### bg <sub><sup>[[MacOS]](src-mac/bg.c)</sup></sub><sub><sup> [[Linux]](src-linux/bg.c)</sup></sub>
###### Usage
`
bg [job id]
`
###### Description
- run the job specified by <*job id*> in the background
- <*job id*> can be found using `jobs`
#

### overkill <sub><sup>[[MacOS]](src-mac/overkill.c)</sup></sub><sub><sup> [[Linux]](src-linux/overkill.c)</sup></sub>
###### Usage
`
overkill
`
###### Description
- kill all background processes
#

### ps <sub><sup>[[MacOS]](src-mac/ps.c)</sup></sub><sub><sup> [[Linux]](src-linux/ps.c)</sup></sub>
###### Usage
`
ps [pid]
`
###### Description
- shows information on the process specified by the pid
- shows shell process information if no argument is passed
#

### set_env <sub><sup>[[MacOS]](src-mac/env.c)</sup></sub><sub><sup> [[Linux]](src-linux/env.c)</sup></sub>
###### Usage
`
set_env [name] [value]
`
###### Description
- sets the environment variable ***name*** to have the specified ***value***
#
 
### unset_env <sub><sup>[[MacOS]](src-mac/env.c)</sup></sub><sub><sup> [[Linux]](src-linux/env.c)</sup></sub>
###### Usage
`
unset_env [name] 
`
###### Description
- unsets the environment variable ***name*** 
#

### cronjob <sub><sup>[[MacOS]](src-mac/cronjob.c)</sup></sub><sub><sup> [[Linux]](src-linux/cronjob.c)</sup></sub>
###### Usage
`
cronjob -c [command] -t [time] -p [period] 
`
###### Description
- executes ***command*** every ***time*** seconds for ***period*** duration
#

# File Structure

```bash
.
├── HEADERS
│   ├── bg.h
│   ├── cd.h
│   ├── cronjob.h
│   ├── echo.h
│   ├── env.h
│   ├── exec.h
│   ├── fg.h
│   ├── help.h
│   ├── history.h
│   ├── jobs.h
│   ├── kjob.h
│   ├── ls.h
│   ├── overkill.h
│   ├── parse.h
│   ├── pcwd.h
│   ├── ps.h
│   ├── processes.h
│   ├── prompt.h
│   ├── redirect.h
│   ├── signals.h
│   ├── sort.h
│   └── utils.h
│
└── SOURCE FILES
    ├── bg.c
    ├── cd.c
    ├── cronjob.c
    ├── echo.c
    ├── env.c
    ├── exec.c
    ├── fg.c
    ├── help.c
    ├── history.c
    ├── jobs.c
    ├── kjob.c
    ├── ls.c
    ├── overkill.c
    ├── parse.c
    ├── pcwd.c
    ├── ps.c
    ├── processes.c
    ├── prompt.c
    ├── redirect.c
    ├── shell.c
    ├── signals.c
    ├── sort.c
    └── utils.c
```

# Naming of the Shell

The **~~s~~** in a~~s~~h is to emphasize the absence of an ***'s'*** before the first ***'h'*** in **Ahish** :stuck_out_tongue: \
The shell is named using the "**\<initial\>SH**" convention

# To-Do

- [ ] Wildcard substitution
- [ ] Memory leaks 😛
  
# Author(s)
  
[Ahish Deshpande](https://ahish9009.github.io)
  
