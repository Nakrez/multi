/**
** @file src/master/arg.h
** @brief Command line arguments processing and configuration management
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/
#ifndef MASTER_ARG_H
# define MASTER_ARG_H

# include <share/error.h>

# include <master/config.h>

/* FIXME doc */
config_t *process_args(int argc, char *argv[]);

#endif /* !MASTER_ARG_H */
