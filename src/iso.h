#ifndef ISO_H_
# define ISO_H_

# include <stddef.h>
# include "iso9660.h"

struct iso
{
    int fd;              /** The file descriptor bound to the iso file */
    void *map;           /** The mapped iso file */
    size_t size;         /** The size of the map */
    struct iso_dir *cwd; /** The current work directory */
};

/**
** Loads an iso file from a filename
** @param[in] filename: the path to the file to load
** @param[out] iso: the iso context to populate
** @returns the newly populated iso context, or NULL if an error occured.
*/
struct iso *iso_load(const char *filename, struct iso *iso);

/**
** Loads an iso file from a file descriptor
** @param[in] fd: the file descriptor of the file to load
** @param[out] iso: the iso context to populate
** @returns the newly populated iso context, or NULL if an error occured.
*/
struct iso *iso_load_fd(int fd, struct iso *iso);

/**
** Unloads the iso context
** @param[in] iso: the iso context to populate
*/
void iso_release(struct iso *iso);

/**
** Loads an iso file from a filename
** @param[in] filename: the path to the file to load
** @param[out] iso: the iso context to populate
** @returns the newly populated iso context, or NULL if an error occured.
*/
struct iso_prim_voldesc *iso_describe(struct iso *iso);

/**
** Returns a pointer to the begining of the nth section
** @param[in] context: the iso context
** @param[in] sector_num: the sector number to seek
** @returns the pointer to the begining of the section
*/
__attribute__ ((always_inline))
inline void *iso_sector(struct iso *context, size_t sector_num)
{
    char *offset = context->map;
    return offset + ISO_BLOCK_SIZE * sector_num;
}

#endif /* !ISO_H_ */
