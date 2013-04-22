#include <master/usage.h>

void usage()
{
    printf("multi %s (compilation date: %s)\n", MULTI_VERSION, __TIMESTAMP__);
    printf("  Configured hosts: %s\n", get_hosts());
    printf("  Configured port: %d\n\n", get_port());

    printf("Copyright(C) 2013 by Baptiste COVOLATO\n\n");

    // FIXME : Add licence

    printf("Usage: multi [--compiler COMPILER] [COMPILER_OPTIONS]");
    printf("-o OUTPUT_FILE -c INPUT_FILE\n\n");

    printf("Options:\n");
    printf("  --compiler COMPILER : Specified to multi the compiler it has");
    printf(" to use\n\n");

    printf("You can set few environnement variable to change multi's");
    printf(" behaviour:\n");

    printf("  MULTI_PORT : Change the default port of multi\n");
    printf("  MULTI_HOSTS : Change the server to which multi will try to");
    printf(" compile your sources\n");
    printf("  MULTI_COMPILER : Change the compiler multi will use ");
    printf("(only if --compiler option is not used)\n");
}
