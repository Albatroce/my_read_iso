#include <stdio.h>

#include "iso.h"
#include "shell.h"
#include "endian.h"

static int print_usage(char *arg0)
{
    printf("usage: %s <iso file>", arg0);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        return print_usage(argv[0]);

    struct iso iso;
    iso_load(argv[1], &iso);

    run(&iso);

    iso_release(&iso);
    return 0;
}
