/**
** @file src/deamon/config.h
** @brief Server configuration related function
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef CONFIG_H
# define CONFIG_H

# include <stdlib.h>
# include <pthread.h>

# include <share/config.h>

typedef struct
{
    /* The socket of the client */
    int cli_fd;

    /* The pthread of the running thread */
    pthread_t thread;
} thread_state_t;

/* Do not be confused : Totally different from client configuration */
typedef struct
{
    /* How many process are running */
    int server_load;

    /* Max load of the server */
    int max_load;

    /* The fd of the main socket */
    int socket_fd;
    /*
    Thread pool : one thread per compilation request
    Max size : number of core of the machine
    */
    thread_state_t *thread_pool;
} config_t;

/**
** @brief Allocate and setup as default a new multi server configuration
**
** @return A new configuration if everything went well
           NULL else
*/
config_t *config_new();

/**
** @brief   Free a server configuration and put it to NULL
            Free only a configuration allocated with @a config_new()
**
** @param   config  The configuration you want to free
*/
void config_free(config_t **config);

/* FIXME : Add doc */
void thread_state_free(thread_state_t **state);

/* FIXME : Add doc */
thread_state_t *thread_state_new();

#endif /* !CONFIG_H */
