CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror

SRCS = main.c iso.c shell.c strtools.c dir.c
CMDS = info.c cd.c ls.c get.c cat.c
OBJS = ${subst .c,.o,${addprefix src/,$(SRCS)} ${addprefix src/cmd/,$(CMDS)}}

all: my_read_iso

my_read_iso: $(OBJS)
	$(LINK.o) -o $@ $^

check: TEST_BIN = ./my_read_iso
check: my_read_iso
	python3 ./check/test.py $(TEST_BIN)

clean:
	$(RM) $(OBJS)

.PHONY: clean check all
