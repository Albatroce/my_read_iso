#include <stdio.h>
#include "strtools.h"

int streq(const char *s1, const char *s2)
{
    for (; *s1 && *s2 && *s1 == *s2; ++s1, ++s2)
        continue;
    return !*s1 && !*s2;
}

int streqn(const char *s1, const char *s2, size_t max)
{
    for (; max && *s1 && *s2 && *s1 == *s2; ++s1, ++s2, --max)
        continue;
    return !max || (!*s1 && !*s2);
}
