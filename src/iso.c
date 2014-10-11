#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "iso.h"
#include "strtools.h"
#include "dir.h"

struct iso *iso_load(const char *filename, struct iso *iso)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        errno = ENOENT;
        return NULL;
    }

    return iso_load_fd(fd, iso);
}

static int validate_iso(struct iso_prim_voldesc *prim)
{
    return (prim->vol_desc_type == 1
         && streqn(prim->std_identifier, "CD001", 5)
         && prim->vol_desc_version == 1);
}

struct iso *iso_load_fd(int fd, struct iso *iso)
{
    struct stat stat;
    if (fstat(fd, &stat) == -1)
        return NULL;

    size_t size = stat.st_size;
    if (size < 0x8000 + sizeof (struct iso_prim_voldesc))
    {
        errno = EINVAL;
        return NULL;
    }

    void *iso_map = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (iso_map == MAP_FAILED)
        return NULL;

    iso->map = iso_map;
    if (!validate_iso(iso_describe(iso)))
    {
        errno = EINVAL;
        return NULL;
    }

    iso->fd = fd;
    iso->size = stat.st_size;
    iso->cwd = get_root(iso);
    return iso;
}

void iso_release(struct iso *iso)
{
    munmap(iso->map, iso->size);
    close(iso->fd);
}

struct iso_prim_voldesc *iso_describe(struct iso *iso)
{
    return iso_sector(iso, ISO_PRIM_VOLDESC_BLOCK);
}
