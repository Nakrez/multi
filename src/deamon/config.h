/**
** @file src/deamon/config.h
** @brief Server configuration related function
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
**
** @license
** Copyright (C) 2013 Baptiste COVOLATO
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to
** deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
** sell copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
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

    int argc;

    char **argv;

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
    Thread pool:    one thread per compilation request
    Max size:       number of core of the machine
    */
    thread_state_t *thread_pool;
} config_t;

/**
** @brief   Allocate and setup as default a new multi server configuration
**
** @return  A new configuration if everything went well
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

/**
** @brief   Allocate a new thread state
**
** @return  The allocated thread state if everything went well
**          NULL else
*/
thread_state_t *thread_state_new();

/**
** @brief   Free a thread state allocated with @a thread_state_new() and set
            it to NULL
**
** @param   state   The thread state you want to free
*/
void thread_state_free(thread_state_t **state);

#endif /* !CONFIG_H */
