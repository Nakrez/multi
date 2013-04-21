#include <master/usage.h>

void usage()
{
    printf("multi %s (compilation date: %s)\n", MULTI_VERSION, __TIMESTAMP__);
    printf("  Configured port %d \n\n", get_port());

    printf("Copyright(C) 2013 by Baptiste COVOLATO\n\n");

    // FIXME : Add licence

    printf("Usage: multi [COMPILER_OPTIONS] -o OUTPUT_FILE -c INPUT_FILE\n");
}
