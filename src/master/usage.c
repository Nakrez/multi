#include <master/usage.h>

void usage()
{
    printf("multi %s (compilation date: %s)\n", MULTI_VERSION, __TIMESTAMP__);
    printf("  Default port %d \n\n", MULTI_PORT);

    printf("Copyright(C) 2013 by Baptiste COVOLATO\n\n");

    // FIXME : Add licence

    printf("Usage: multi [COMPILER_OPTIONS] -c INPUT_FILE -o OUTPUT_FILE\n");
}
