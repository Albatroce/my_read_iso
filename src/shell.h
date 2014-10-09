#ifndef SHELL_H_
# define SHELL_H_

# include "iso.h"

# define MAX_COMMAND_SIZE 1024

void run(struct iso *context);
int validate_cmd_args(const char *name, int actual, int expected);

#endif /* !SHELL_H_ */
