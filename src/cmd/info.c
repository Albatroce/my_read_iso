#include <stdio.h>

#include "../endian.h"
#include "info.h"

void info(struct iso *context, int argc, char *argv[])
{
    argc += 0;
    argv[0] += 0;

    struct iso_prim_voldesc *desc = iso_describe(context);
    printf(OUTPUT,
           desc->syidf,
           desc->vol_idf,
           endian32_value(desc->vol_blk_count),
           endian16_value(desc->vol_blk_size),
           desc->date_creat,
           desc->app_idf);
}
