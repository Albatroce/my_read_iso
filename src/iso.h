#ifndef ISO_H_
# define ISO_H_

# include <stddef.h>
# include "iso9660.h"

struct iso
{
    int fd;
    void *map;
    size_t size;
    struct iso_dir *cwd;
};

struct iso *iso_load(const char *filename, struct iso *iso);
struct iso *iso_load_fd(int fd, struct iso *iso);
void iso_release(struct iso *iso);
struct iso_prim_voldesc *iso_describe(struct iso *iso);

__attribute__ ((always_inline))
inline void *iso_sector(struct iso *context, size_t sector_num)
{
    char *offset = context->map;
    return offset + ISO_BLOCK_SIZE * sector_num;
}

#endif /* !ISO_H_ */
