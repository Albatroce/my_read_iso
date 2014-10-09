#ifndef DIR_H_
# define DIR_H_

# include "iso.h"

struct iso_dir *setcwd(struct iso *context, const char *dir);
struct iso_dir *get_root(struct iso *context);
char *dirname(struct iso_dir *dir, char *out);

void walk(struct iso *context,
          struct iso_dir *dir,
          void (*callback)(struct iso_dir *));

#endif /* !DIR_H_ */
