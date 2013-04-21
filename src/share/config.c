#include <share/config.h>

int get_port()
{
    char *port = getenv("MULTI_PORT");

    if (port)
        return atoi(port);

    return DEFAULT_MULTI_PORT;
}
