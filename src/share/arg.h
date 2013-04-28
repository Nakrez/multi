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

/**
** @brief   Add argumtent to an array of argument. Be carefull the function does
            does not increment @a argc
**
** @param   argc    The number of argument in the array
** @param   argv    The array containing the arguments
** @param   str     The argument to add to the array
**
** @return  0 if everything went well, -1 else
*/
int add_argv(int argc, char ***argv, char *str);

/**
** @brief Concatenate array of arguments in one string
**
** @param   argc    The number of argument in the array
** @param   argv    The array containing the arguments
** @param   result  The resulting string of the concatenation
**
** @return  The size of the string if everything went well, -1 else
*/
int concate_argv(int argc, char **argv, char **result);

/**
** @brief Split string into an array of argument
**
** @param   argv    The string to split
** @param   result  The resulting array. Desallocate this array is the duty of
                    the caller
**
** @return  The size of the resulting array. Error not handled yet
*/
int split_argv(char *argv, char ***result);

/**
** @brief   Find input and output file in the array of argument and replace it
            with @a input_file and @a output_file
**
** @param   argc        The number of argument in the array
** @param   argv        The array containing the arguments
** @param   input_file  The new input file name
** @param   output_file The new output file name
*/
void update_argv_file(int argc, char **argv, char *input_file,
                      char *output_file);

#endif /* !SHARE_ARG_H */
