.PHONY:
	all 

CC = gcc
FLAGS = -Wall
INC-MAC = -I include-mac

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ash

mac: ash-mac

ash-mac: 
	$(CC) $(FLAGS) $(INC-MAC) -o ash $(SRCS)

clean:
	rm ash;
