/**
** @file src/share/config.h
** @brief Multi internal configuration file
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef SHARE_CONFIG_H
# define SHARE_CONFIG_H

# include <unistd.h>
# include <stdlib.h>

/* The size of the queue of the server */
# define SOCKET_QUEUE 5

/* The port Multi use */
# define DEFAULT_MULTI_PORT 8216

# define DEFAULT_MULTI_HOST "127.0.0.1"
/*
The number max of concurent compile unit accepted by a server
Limit : The number of core online
*/
# define THREAD_COMPILE_MAX sysconf(_SC_NPROCESSORS_ONLN)

# define MULTI_VERSION "1.0.0"

/**
** @brief Get the port multi (client or server) have to use
**
** @return The port to use
*/
int get_port();

/**
** @brief Get all server the client can connect
**
** @return all hosts separated by spaces
*/
char *get_hosts();

#endif /* !SHARE_CONFIG_H */
