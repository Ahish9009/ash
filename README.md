# as̶h
Custom shell in low level C

# Usage

##### Clone the repo
`
git clone https://github.com/Ahish9009/ash/
`
##### Navigate into it 
`
cd ash
`
##### Generate the binary executable
###### *on Linux*:
`
make linux
`
###### *on MacOS*:
`
make mac
`
##### Execute 
`
./ash
`
# Features
- Supports semi-colon separated commands
- Supports multiple piping
- Supports input & output redirection
- Allows job control/process management
  - Jobs can be run in the foreground or background
- Stores command history
- Handles/traps signals

# Built-in Commands

### ls
###### Usage: 
`
ls -[al] [path/to/dir]
`
###### Description
- Lists files in the specified directory *(lists files of the current directory if no path is specified)*
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








## Features

- [x] ';' separated commands
- [x] Piping (multiple)
- [x] Redirection
- [x] fg/bg
- [x] Built-in commands
  - [x] echo
  - [x] ls
  - [x] cd
  - [x] pwd
  
