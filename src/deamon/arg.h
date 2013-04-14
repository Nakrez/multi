/**
** @file src/deamon/arg.h
** @brief Command line argument processing for server
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef ARG_H
# define ARG_H

# include <string.h>

enum server_behaviour_e
{
    SERVER_USAGE,
    SERVER_START,
    SERVER_RESTART,
    SERVER_STOP,
    SERVER_PID
};

enum server_behaviour_e parse_arg(int argc, char *argv[]);

#endif /* !ARG_H */
