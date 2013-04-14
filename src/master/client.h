/**
** @file src/master/client.h
** @brief Main functions of the client
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef CLIENT_H
# define CLIENT_H

# include <master/config.h>
# include <master/arg.h>

# include <share/socket.h>
# include <share/compile.h>

/* FIXME doc */
int launch_client(int argc, char *argv[]);

#endif /* !CLIENT_H */
