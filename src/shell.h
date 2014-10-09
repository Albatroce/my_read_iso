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

void run(struct iso *context);
int validate_cmd_args(const char *name, int actual, int expected);

#endif /* !SHELL_H_ */
