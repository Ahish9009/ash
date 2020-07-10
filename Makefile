.PHONY:
	all 

CC = gcc
FLAGS = -Wall

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ash

ash: 
	$(CC) $(FLAGS) -o $@ $(SRCS)

clean:
	rm ash;
