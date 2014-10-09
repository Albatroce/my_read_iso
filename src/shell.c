#include <unistd.h>
#include <stdio.h>

#include "shell.h"
#include "strtools.h"
#include "cmd/info.h"
#include "cmd/cd.h"
#include "cmd/ls.h"
#include "cmd/get.h"
#include "cmd/cat.h"

#define ARG_ERROR_FORMAT "my_read_iso: %s: %s\n"

static int running = 1;

typedef void (*f_command)(struct iso *, int, char *[]);

int validate_cmd_args(const char *name, int actual, int expected)
{
    if (actual != expected)
    {
        char *message = "";
        if (expected == 0)
            message = "command does not take an argument";
        else if (expected == 1)
            message = "command requires an argument";
        fprintf(stderr, ARG_ERROR_FORMAT, name, message);
    }
    return actual == expected;
}

static void noop(struct iso *context, int argc, char *argv[])
{
    context += 0;
    argc += 0;
    argv += 0;

    fprintf(stderr, "my_read_iso: %s: unknown command\n", argv[0]);
}

static void help(struct iso *context, int argc, char *argv[])
{
    context += 0;
    if (validate_cmd_args(argv[0], argc - 1, 0))
        printf(HELP_STRING);
}

static void quit(struct iso *context, int argc, char *argv[])
{
    context += 0;
    if (validate_cmd_args(argv[0], argc - 1, 0))
        running = 0;
}

static f_command get_command(const char *cmd)
{
    if (streq(cmd, "info"))
        return info;
    if (streq(cmd, "cd"))
        return cd;
    if (streq(cmd, "ls"))
        return ls;
    if (streq(cmd, "get"))
        return get;
    if (streq(cmd, "cat"))
        return cat;
    if (streq(cmd, "help"))
        return help;
    if (streq(cmd, "quit"))
        return quit;
    return noop;
}

static int is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static void swap(char **tab, size_t i, size_t j)
{
    char *tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

static char *prompt(char *buffer, size_t size)
{
    if (isatty(STDIN_FILENO))
    {
        printf("> ");
        fflush(stdout);
    }
    return fgets(buffer, size, stdin);
}

void run(struct iso *context)
{
    char cmd[MAX_COMMAND_SIZE + 1];

    while (running && prompt(cmd, MAX_COMMAND_SIZE + 1))
    {
        int argc = 0;
        char *argv[MAX_COMMAND_SIZE];

        ssize_t read_b = 0;
        for (char *s = cmd; *s; ++s)
            ++read_b;

        char *s = cmd + read_b - 1;
        for (; read_b > 0; --read_b, --s)
        {
            for (; read_b > 0 && is_whitespace(*s); --read_b, --s)
                continue;
            if (read_b)
            {
                *(s + 1) = '\0';
                for (; read_b > 0 && !is_whitespace(*s); --read_b, --s)
                    continue;
                argv[argc++] = s + 1;
            }
        }

        if (!argc)
            continue;

        for (int i = 0; i < argc / 2; ++i)
            swap(argv, i, argc - i - 1);

        get_command(argv[0])(context, argc, argv);
    }
}
