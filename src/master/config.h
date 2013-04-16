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

/* FIXME doc */
typedef struct
{
    multi_file_t *file;

    compile_result_t *result;

    int socket_fd;

    char *argv[];
} config_t;

/* FIXME doc */
config_t *config_new();

/* FIXME doc */
void config_free(config_t **config);

#endif /* !MASTER_CONFIG_H */
