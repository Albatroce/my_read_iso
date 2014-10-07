#ifndef CMD_INFO_H_
# define CMD_INFO_H_

# include "../iso.h"
# include "../iso9660.h"

# define XSTR(s) #s
# define STRING(s) XSTR(s)

# define OUTPUT                                                 \
        "System Identifier: %." STRING(ISO_SYSIDF_LEN) "s\n"    \
        "Volume Identifier: %." STRING(ISO_VOLIDF_LEN) "s\n"    \
        "Block count: %u\n"                                     \
        "Block size: %u\n"                                      \
        "Creation date: %." STRING(ISO_LDATE_LEN) "s\n"         \
        "Application Identifier: %." STRING(ISO_APP_LEN) "s\n"

void info(struct iso *context);

#endif /* !CMD_INFO_H_ */
