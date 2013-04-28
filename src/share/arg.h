/**
** @file src/share/arg.h
** @brief Command line arguments general operations
** @date 04/18/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/
#ifndef SHARE_ARG_H
# define SHARE_ARG_H

# include <stdlib.h>
# include <string.h>

# include <share/utils.h>

/**
** @brief   Duplicate existing argument array
            Be carreful no deep copy of each arguments is performed
            The destruction of the allocated array is let to the user
**
** @param   argc    The number of arguments
** @param   argv    The array containing the arguments to copy
**
** @return  The duplicate argument array, NULL if it fails
*/
char **dup_argv(int argc, char **argv);

/* FIXME doc */
void add_argv(int argc, char ***argv, char *str);

/* FIXME doc */
int concate_argv(int argc, char **argv, char **result);

/* FIXME doc */
int split_argv(char *argv, char ***result);

/* FIXME doc */
void update_argv_file(int argc, char **argv, char *input_file,
                      char *output_file);

#endif /* !SHARE_ARG_H */
