#ifndef ISO_H_
# define ISO_H_

# include <stddef.h>
# include "iso9660.h"

struct iso
{
    int fd;
    void *map;
    size_t size;
};

void iso_load(const char *filename, struct iso *iso);
void iso_load_fd(int fd, struct iso *iso);
void iso_release(struct iso *iso);
struct iso_prim_voldesc *iso_describe(struct iso *iso);

#endif /* !ISO_H_ */
