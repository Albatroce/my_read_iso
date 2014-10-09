#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "cd.h"
#include "../dir.h"

static const char *get_message(void *result)
{
    if (!result)
    {
        switch (errno)
        {
        case ENOENT:
            return "unable to find '%s' directory entry\n";
        case ENOTDIR:
            return "entry '%s' is not a directory\n";
        default:
            return "an unexpected error occured while trying to cd to '%s'\n";
        }
    }
    else
        return "Changing to '%s' directory\n";
}

void cd(struct iso *context, int argc, char *argv[])
{
    char *dirname = "root dir";
    void *res = setcwd(context, argc < 2 ? NULL : (dirname = argv[1]));
    fprintf(res ? stdout : stderr, get_message(res), dirname);
}
