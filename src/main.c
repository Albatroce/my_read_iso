#include <stdio.h>
#include <errno.h>
#include <string.h>

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
    if (!iso_load(argv[1], &iso))
    {
        fprintf(stderr,
                "my_read_iso: %s: %s\n",
                argv[1],
                errno == EINVAL ? "invalid ISO9660 file" : strerror(errno));
        return 1;
    }

    run(&iso);

    iso_release(&iso);
    return 0;
}
