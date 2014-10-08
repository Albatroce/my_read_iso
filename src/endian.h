#ifndef ENDIAN_H_
# define ENDIAN_H_

# include "iso9660.h"

/**
 ** Utilities to deal with endianness in iso file
 */

# if   __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__      \
    && __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#  error "only LSB & MSB byte orders are supported."
# endif

__attribute__ ((always_inline))
inline uint32_t endian32_value(struct endian32 e)
{
# if   __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return e.le;
# elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return e.be;
# endif
}

__attribute__ ((always_inline))
inline uint16_t endian16_value(struct endian16 e)
{
# if   __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return e.le;
# elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return e.be;
# endif
}

#endif /* !ENDIAN_H_ */
