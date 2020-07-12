.PHONY:
	all 

CC = gcc
FLAGS = -Wall
INC = -I include

SRCS-LINUX := $(wildcard src-linux/*.c)
SRCS-MAC := $(wildcard src-mac/*.c)
BINS := $(SRCS:%.c=%)

all: ash

mac: ash-mac
linux: ash-linux

ash-mac: 
	$(CC) $(FLAGS) $(INC) -o ash $(SRCS-MAC)

ash-linux: 
	$(CC) $(FLAGS) $(INC) -o ash $(SRCS-LINUX)

clean:
	rm ash;
