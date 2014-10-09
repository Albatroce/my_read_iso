#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "cat.h"
#include "../dir.h"
#include "../shell.h"
#include "../endian.h"

void cat(struct iso *context, int argc, char *argv[])
{
    if (!validate_cmd_args(argv[0], argc - 1, 1))
        return;

    struct iso_dir *file = get_file(context, context->cwd, argv[1]);
    if (!file)
        DIE("unable to find '%s' entry\n", argv[1]);
    if (file->type & iso_file_isdir)
        DIE("entry '%s' is a directory\n", argv[1]);

    void *ptr = iso_sector(context, endian32_value(file->data_blk));
    uint32_t size = endian32_value(file->file_size);
    if (write(STDOUT_FILENO, ptr, size) == -1)
        DIE("my_read_iso: %s: %s\n", argv[1], strerror(errno));
}
