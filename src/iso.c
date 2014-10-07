#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "iso.h"

void iso_load(const char *filename, struct iso *iso)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;

    iso_load_fd(fd, iso);
}

void iso_load_fd(int fd, struct iso *iso)
{
    struct stat stat;
    if (fstat(fd, &stat) == -1)
        return;

    void *iso_map = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (iso_map == MAP_FAILED)
        return;

    iso->fd = fd;
    iso->map = iso_map;
    iso->size = stat.st_size;
}

void iso_release(struct iso *iso)
{
    munmap(iso->map, iso->size);
    close(iso->fd);
}

struct iso_prim_voldesc *iso_describe(struct iso *iso)
{
    char *offset = iso->map;
    offset += ISO_BLOCK_SIZE * ISO_PRIM_VOLDESC_BLOCK;
    void *primary_block = offset;
    return primary_block;
}
