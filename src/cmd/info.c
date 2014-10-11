#include <stdio.h>

#include "../endian.h"
#include "../shell.h"
#include "info.h"

void info(struct iso *context, int argc, char *argv[])
{
    if (!validate_cmd_args(argv[0], argc - 1, 0))
        return;

    struct iso_prim_voldesc *desc = iso_describe(context);
    printf(OUTPUT,
           desc->syidf,
           desc->vol_idf,
           endian32_value(desc->vol_blk_count),
           endian16_value(desc->vol_blk_size),
           desc->date_creat,
           desc->app_idf);
}
