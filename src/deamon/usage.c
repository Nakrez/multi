#include <deamon/usage.h>

void usage()
{
    printf("multi-server %s (compilation date: %s)\n",
            MULTI_VERSION,
            __TIMESTAMP__);
    printf("  Configured port %d \n\n", get_port());

    printf("Copyright(C) 2013 by Baptiste COVOLATO\n\n");

    // FIXME : Add licence

    printf("Usage: multi OPTION\n");

    printf("Options:\n");
    printf("  --start : Start a new multi server if no server is running\n");
    printf("  --stop : Stop the running multi server\n");
    printf("  --restart : Restart running multi server or start a new one\n");
    printf("  --pid : Print the pid of the running multi server\n");
}
