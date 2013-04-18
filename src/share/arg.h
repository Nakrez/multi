/**
** @file src/share/arg.h
** @brief Command line arguments general operations
** @date 04/18/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/
#ifndef SHARE_ARG_H
# define SHAREARG_H

# include <stdlib.h>
# include <string.h>

/* FIXME doc */
char **dup_argv(int argc, char **argv);

/* FIXME doc */
void add_argv(int argc, char ***argv, char *str);

/* FIXME doc */
int concate_argv(int argc, char **argv, char **result);

#endif /* !ARG_H */
