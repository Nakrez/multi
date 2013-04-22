#include <share/config.h>

int get_port()
{
    char *port = getenv("MULTI_PORT");

    if (port)
        return atoi(port);

    return DEFAULT_MULTI_PORT;
}

char *get_hosts()
{
    char *hosts = getenv("MULTI_HOSTS");

    if (hosts)
        return hosts;

    return DEFAULT_MULTI_HOST;
}
