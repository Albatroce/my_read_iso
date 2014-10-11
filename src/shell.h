#ifndef SHELL_H_
# define SHELL_H_

# include "iso.h"

# define MAX_COMMAND_SIZE 1024

# define DIE(...)                       \
    do {                                \
        fprintf(stderr, __VA_ARGS__);   \
        return;                         \
    } while(0);

# define HELP_STRING                        \
    "help\t: display command help\n"        \
    "info\t: display volume info\n"         \
    "ls\t: display directory content\n"     \
    "cd\t: change current directory\n"      \
    "get\t: copy file to local directory\n" \
    "cat\t: display file content\n"         \
    "quit\t: program exit\n"

/**
** The main shell function -- reads commands from stdin until no more bytes
** are available or the 'quit' command is given.
** @param[in] context: the iso context
*/
void run(struct iso *context);

/**
** Validates that the argument size are as expected, and prints an error
** otherwise.
** @param[in] name: the name of the command (purely cosmetic for the message)
** @param[in] actual: the actual argument count
** @param[in] expected: the expected argument count
** @returns 1 if the command has been validated, 0 othervise
*/
int validate_cmd_args(const char *name, int actual, int expected);

#endif /* !SHELL_H_ */
