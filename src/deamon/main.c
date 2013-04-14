#include <stdio.h>

#include <deamon/usage.h>
#include <deamon/arg.h>
#include <deamon/server.h>

int main(int argc, char *argv[])
{
    switch (parse_arg(argc, argv))
    {
        case SERVER_USAGE:
            usage();
            return 0;
        case SERVER_START:
            return server_start();
        case SERVER_RESTART:
            printf("Option not handled yet\n");
            break;
        case SERVER_STOP:
            printf("Option not handled yet\n");
            break;
        case SERVER_PID:
            printf("Option not handled yet\n");
            break;
    }

    return 1;
}
