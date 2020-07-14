# as̶h
Custom shell in low level C

# Usage

##### Clone the repo
```bash
git clone https://github.com/Ahish9009/ash/
```
##### Navigate into it 
```bash
cd ash
```
##### Generate the binary executable
###### *on Linux*:
```bash
make linux
```
###### *on MacOS*:
```bash
make mac
```
##### Execute 
```bash
./ash
```

# Built-in Commands

### ls
###### Usage:
```bash
ls -[al] [path/to/dir]
```
- Lists files in the specified directory *(lists files of the current directory if no path is specified)*
___

### cd
###### Usage:
```bash
cd [path/to/dir]
```
###### Description
- Changes working directory to the path specified
- Accepts both *absolute* and *relative* paths
###### Options
- `cd -` : switches to the *previous* working directory
- `cd` : switches to the *root* directory
___

### pwd
###### Usage:
```bash
pwd
```
###### Description
- returns the name of the current working directory 
___

### echo
###### Usage:
```bash
echo -[n] [string ...]
```
###### Description
- write arguments to the standard output
###### Options
- `-n` : does not print the trailing newline character
___

### jobs
###### Usage:
```bash
jobs
```
###### Description
- display status of jobs in the current session
___

### kjob
###### Usage:
```bash
kjob <signal number> [pid ...]
```
###### Description
- send the specified signal to the specified processes
- Multiple pids can be passed
---

### history
###### Usage:
```bash
history [n]
```
###### Description
- displays the history of commands
- passing a number *n* as argument displays the last *n* entries
___

### fg
###### Usage:
```bash
fg [job id]
```
###### Description
- runs the job specified by *<job id>* in the background 
- *job id* can be found using `jobs`
___

### bg
###### Usage:
```bash
fg [job id]
```
###### Description
- run the job specified by *<job id>* in the background
- *<job id>* can be found using `jobs`
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
  
