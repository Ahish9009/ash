null :=
space := ${null} ${null}
${space} := ${space}
define \n


endef

.PHONY:
	all 

CC = gcc
FLAGS = -Wall
INC = -I include

SRCS-LINUX := $(wildcard src-linux/*.c)
SRCS-MAC := $(wildcard src-mac/*.c)

BINS := $(SRCS:%.c=%)

all: ash-mac

mac: ash-mac
linux: ash-linux

ash-mac: 
	$(info MAC:)
	$(info ${\n}> Sources:)
	$(info $(subst ${ },${\n},${SRCS-MAC}))
	$(info ${\n}> Compiling...)

	$(CC) $(FLAGS) $(INC) -o ash $(SRCS-MAC)

ash-linux: 
	$(info LINUX:)
	$(info ${\n}> Sources:)
	$(info $(subst ${ },${\n},${SRCS-LINUX}))
	$(info ${\n}> Compiling...)

	$(CC) $(FLAGS) $(INC) -o ash $(SRCS-LINUX)

clean:
	rm ash
