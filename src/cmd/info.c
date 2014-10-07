#include <stdio.h>

#include "info.h"

void info(struct iso *context)
{
    struct iso_prim_voldesc *desc = iso_describe(context);
    printf(OUTPUT,
           desc->syidf,
           desc->vol_idf,
           desc->vol_blk_count.le,
           desc->vol_blk_size.le,
           desc->date_creat,
           desc->app_idf);
}
