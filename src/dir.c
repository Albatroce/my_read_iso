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

static int translate(const char *in, char *out)
{
    switch (*in)
    {
    case 0:
        out[0] = '.';
        return 1;
    case 1:
        out[0] = '.';
        out[1] = '.';
        return 2;
    default:
        out[0] = in[0];
        return 1;
    }
}

char *dirname(struct iso_dir *dir, char *out)
{
    const char *raw = shift(dir, sizeof (struct iso_dir));
    size_t i = 0;
    if (dir->idf_len == 1)
        i = translate(raw, out);
    else
        for (; i < dir->idf_len; ++i)
            out[i] = raw[i];
    out[i] = '\0';
    return out;
}

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

struct iso_dir *setcwd(struct iso *context, const char *dir)
{
    if (!dir)
        context->cwd = get_root(context);
    else
    {
        uint32_t sector = endian32_value(context->cwd->data_blk);
        struct iso_dir *d;
        for (d = iso_sector(context, sector);
             d->dir_size;
             d = shift(d, d->dir_size))
        {
            char name[d->idf_len + 3];
            dirname(d, name);
            if (streqn(name, dir, realsize(d)))
                break;
        }
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

void walk(struct iso *context,
          struct iso_dir *dir,
          void (*callback)(struct iso_dir *))
{
    uint32_t sector = endian32_value(dir->data_blk);
    struct iso_dir *d;
    for (d = iso_sector(context, sector);
         d->dir_size;
         d = shift(d, d->dir_size))
        callback(d);
}

