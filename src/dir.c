#include <errno.h>

#include "dir.h"
#include "endian.h"
#include "strtools.h"

struct iso_dir *get_root(struct iso *context)
{
    return &iso_describe(context)->root_dir;
}

static void *shift(void *ptr, size_t shift)
{
    char *offset = ptr;
    return offset + shift;
}

const char *dirname(struct iso_dir *dir)
{
    return shift(dir, sizeof (struct iso_dir));
}

static size_t realsize(struct iso_dir *dir, size_t s)
{
    const char *name = dirname(dir);
    size_t len = 0;
    for (; len < s && *name != ';'; ++name, ++len)
        continue;
    return len;
}

struct iso_dir *setcwd(struct iso *context, const char *dir)
{
    if (!dir)
        context->cwd = get_root(context);
    else
    {
        uint32_t sector = endian32_value(context->cwd->data_blk);
        struct iso_dir *d;
        for (d = iso_sector(context, sector);
             d->dir_size && !streqn(dirname(d), dir, realsize(d, d->idf_len));
             d = shift(d, d->dir_size))
            continue;
        if (!d->dir_size)
        {
            errno = ENOENT;
            return NULL;
        }
        if (!(d->type & iso_file_isdir))
        {
            errno = ENOTDIR;
            return NULL;
        }
        context->cwd = d;
    }
    return context->cwd;
}
