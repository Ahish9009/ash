.PHONY:
	all 

CC = gcc
FLAGS = -Wall
INC-MAC = -I include-mac
INC-LINUX = -I include-linux

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ash

mac: ash-mac
linux: ash-linux

ash-mac: 
	$(CC) $(FLAGS) $(INC-MAC) -o ash $(SRCS)

ash-linux: 
	$(CC) $(FLAGS) $(INC-LINUX) -o ash $(SRCS)

clean:
	rm ash;
