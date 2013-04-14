/**
** @file src/deamon/server.h
** @brief Main functions of server
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef SERVER_H
# define SERVER_H

# include <sys/time.h>

# include <share/socket.h>
# include <share/error.h>

# include <deamon/config.h>
# include <deamon/file.h>

// FIXME : Doc
int server_start();

# define INCR_SERVER_LOAD                                   \
    do                                                      \
    {                                                       \
        pthread_mutex_lock(&server_mutex);                  \
        ++(server_config->server_load);                     \
        pthread_mutex_unlock(&server_mutex);                \
    } while (0)

# define DECR_SERVER_LOAD                                   \
    do                                                      \
    {                                                       \
        pthread_mutex_lock(&server_mutex);                  \
        --(server_config->server_load);                     \
        pthread_mutex_unlock(&server_mutex);                \
    } while (0)

#endif /* !SERVER_H */
