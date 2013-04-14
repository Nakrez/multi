/**
** @file src/master/arg.h
** @brief Command line arguments processing and configuration management
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/
#ifndef MASTER_ARG_H
# define MASTER_ARG_H

# include <share/error.h>

# include <master/file.h>

typedef struct
{
    multi_file *file;

    char *argv[];
} config_t;

config_t *process_args(int argc, char *argv[]);

void destroy_config(config_t **config);

#endif /* !MASTER_ARG_H */
