.PHONY:
	all 

CC = gcc
FLAGS = -Wall
INC = -I include

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ash

ash: 
	$(CC) $(FLAGS) $(INC) -o $@ $(SRCS)

clean:
	rm ash;
