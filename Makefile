CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -g

SRCS = main.c iso.c shell.c
CMDS = info.c
OBJS = ${subst .c,.o,${addprefix src/,$(SRCS)} ${addprefix src/cmd/,$(CMDS)}}

all: my_read_iso

my_read_iso: $(OBJS)
	$(LINK.o) -o $@ $^

clean:
	$(RM) $(OBJS)
