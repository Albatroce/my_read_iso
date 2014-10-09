#include <stdio.h>

#include "ls.h"
#include "../dir.h"
#include "../shell.h"
#include "../endian.h"

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

static void print_file(struct iso_dir *f)
{
    size_t len = realsize(f);
    char name[len + 1];
    name[len] = '\0';

    char rawname[f->idf_len + 3];
    dirname(f, rawname);
    for (size_t i = 0; i < len; ++i)
        name[i] = rawname[i];

    printf("%c%c %9u %s\n",
           (f->type & iso_file_isdir) ? 'd' : '-',
           (f->type & iso_file_hidden) ? 'h' : '-',
           endian32_value(f->file_size),
           name);
}

void ls(struct iso *context, int argc, char *argv[])
{
    if (validate_cmd_args(argv[0], argc - 1, 0))
        walk(context, context->cwd, print_file);
}
