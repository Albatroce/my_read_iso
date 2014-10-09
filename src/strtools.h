#ifndef STRTOOLS_H_
# define STRTOOLS_H_

# include <stddef.h>

/**
 ** Compares two strings for equality.
 ** @param[in] s1 The first string
 ** @param[in] s2 The second string
 ** @returns 1 if the two strings are equal; 0 otherwise.
 */
int streq(const char *s1, const char *s2);

/**
 ** Compares two strings for equality, with a maximum length.
 ** @param[in]  s1 The first string
 ** @param[in]  s2 The second string
 ** @param[in] max The maximum length of both strings.
 ** @returns 1 if the first "max" characters in both
 **          strings are equal; 0 otherwise.
 */
int streqn(const char *s1, const char *s2, size_t max);

#endif /* !STRTOOLS_H_ */
