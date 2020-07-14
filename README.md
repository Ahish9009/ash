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

# Built-in Commands

###### 1
### ls
###### Usage: `ls -[al] [path/to/dir]`
- Lists files in the specified directory *(lists files of the current directory if no path is specified)*
___

###### 2
### cd
###### Usage: `cd [path/to/dir]`
###### Description
- Changes working directory to the path specified
- Accepts both *absolute* and *relative* paths
###### Options
- `cd -` : switches to the *previous* working directory
- `cd` : switches to the *root* directory
___

###### 3
### pwd
###### Usage:
`
pwd
`
###### Description
- returns the name of the current working directory 
___

###### 4
### echo
###### Usage:
`
echo -[n] [string ...]
`
###### Description
- write arguments to the standard output
###### Options
- `-n` : does not print the trailing newline character
___

###### 5
### jobs
###### Usage:
`
jobs
`
###### Description
- display status of jobs in the current session
___

###### 6
### kjob
###### Usage:
`
kjob <signal number> [pid ...]
`
###### Description
- send the specified signal to the specified processes
- Multiple pids can be passed
---

###### 7
### history
###### Usage:
`
history [n]
`
###### Description
- displays the history of commands
- passing a number *n* as argument displays the last *n* entries
___

###### 8
### fg
###### Usage:
`
fg [job id]
`
###### Description
- runs the job specified by <*job id*> in the foreground 
- <*job id*> can be found using `jobs`
___

###### 9
### bg
###### Usage:
`
bg [job id]
`
###### Description
- run the job specified by <*job id*> in the background
- <*job id*> can be found using `jobs`
___





## Features

- [x] ';' separated commands
- [x] Piping (multiple)
- [x] Redirection
- [ ] fg/bg
- [ ] Built-in commands
  - [ ] echo
  - [ ] ls
  - [ ] cd
  - [ ] pwd
  
