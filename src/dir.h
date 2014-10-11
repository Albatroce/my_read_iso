#ifndef DIR_H_
# define DIR_H_

# include "iso.h"

/**
** Changes the current work directory
** @param[in] context: the iso context
** @param[in] dir: the directory name
** @returns the new current work directory, or NULL if an error occured.
**
** When the returned value is NULL, errno is set to the following values:
** * ENOENT: the specified file does not exist
** * ENOTDIR: the specified file exists but is not a directory
*/
struct iso_dir *setcwd(struct iso *context, const char *dir);

/**
** Gets the root of the filesystem
** @param[in] context: tthe iso context
** @returns the root directory
*/
struct iso_dir *get_root(struct iso *context);

/**
** Gives the name of the specified directory
** @param[in] dir: the directory to get the name from
** @param[out] out: the buffer to write the name to
** @returns the pointer of out
**
** The function does not check if the passed buffer is of sufficient size.
*/
char *dirname(struct iso_dir *dir, char *out);

/**
** Gets a file inside the specified directory from its name.
** @param[in] context: the iso context
** @param[in] dir: the directory to get the file from
** @param[in] filename: the name of the file to get
** @returns the file or NULL if the file does not exist.
*/
struct iso_dir *get_file(struct iso *context,
                         struct iso_dir *dir,
                         const char *filename);

/**
** Walks in a directory and calls the specified function on each of
** its children.
** @param[in] context: the iso context
** @param[in] dir: the directory to walk
** @param[in] callback: the function to call on each child
*/
void walk(struct iso *context,
          struct iso_dir *dir,
          void (*callback)(struct iso_dir *));

#endif /* !DIR_H_ */
