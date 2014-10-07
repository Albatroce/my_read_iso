#include <string.h>

#include "iso.h"
#include "cmd/info.h"

typedef void (*f_command)(struct iso *);

void noop(struct iso *context)
{
}

// fixme
f_command get_command(const char *cmd)
{
    if (!strcmp(cmd, "info"))
        return info;
    else
        return noop;
}

void run(struct iso *context)
{

}
