#include <deamon/arg.h>

enum server_behaviour_e parse_arg(int argc, char *argv[])
{
    if (argc != 2)
        return SERVER_USAGE;

    if (!strcmp(argv[1], "--start"))
        return SERVER_START;
    else if (!strcmp(argv[1], "--restart"))
        return SERVER_RESTART;
    else if (!strcmp(argv[1], "--stop"))
        return SERVER_STOP;
    else if (!strcmp(argv[1], "--pid"))
        return SERVER_PID;

    /* Wrong option passed */
    return SERVER_USAGE;
}
