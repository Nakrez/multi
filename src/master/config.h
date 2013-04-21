/**
** @file src/master/config.h
** @brief Configuration of the client
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/
#ifndef MASTER_CONFIG_H
# define MASTER_CONFIG_H

# include <unistd.h>

# include <share/compile.h>

# include <master/file.h>

/**
** @brief The configuration structure used by the client
*/
typedef struct
{
    /* Name of the input/output file and the language (not supported yet) */
    multi_file_t *file;

    /* The compilation result send back by the server */
    compile_result_t *result;

    /* The socket file descriptor used to communicate with the server */
    int socket_fd;

    /* Indicate if the compilation has to be run locally */
    int local;

    /* The number of arguments passed to the client by the command line */
    int argc;

    /* Arguments passed to the client by the command line */
    char **argv;

    /* The number of servers */
    int nb_server;

    /* The list of servers (Ip adresses) */
    char **servers;
} config_t;

/**
** @brief Create a new configuration structure for the client
**
** @return The created configuration if everything went well, NULL else
*/
config_t *config_new();

/**
** @brief Free client configuration allocated with @a config_new()
**
** @param   config  The config you want to free
*/
void config_free(config_t **config);

#endif /* !MASTER_CONFIG_H */
