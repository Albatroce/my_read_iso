#include <stdio.h>

#include "ls.h"
#include "../dir.h"

static size_t realsize(struct iso_dir *dir)
{
    size_t s = dir->idf_len + 3;
    char name[s];
    dirname(dir, name);
    size_t len = 0;
    for (char *str = name; *str && len < s && *str != ';'; ++str, ++len)
        continue;
    return len;
}

void print_file(struct iso_dir *f)
{
    size_t len = realsize(f);
    char name[len + 1];
    name[len] = '\0';

    char rawname[f->idf_len + 3];
    dirname(f, rawname);
    for (size_t i = 0; i < len; ++i)
        name[i] = rawname[i];

    printf("%c%c\t%d %s\n", '-', '-', 0, name);
}

void ls(struct iso *context, int argc, char *argv[])
{
    walk(context, context->cwd, print_file);
}
