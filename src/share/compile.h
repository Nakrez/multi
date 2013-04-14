/**
** @file src/share/compile.h
** @brief All compilation related function
** @date 04/14/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef COMPILE_H
# define COMPILE_H

# include <unistd.h>

# include <stdlib.h>

# include <sys/wait.h>
# include <sys/types.h>

/**
** @brief Run preprocess if needed
** @param input_file    The file you want to preprocess
** @param output_file   The file where you want to put the result of the
                        preprocessing operation
**
** @return The value returned by the compiler
**         -1 if an error occured before compiler instanciation
*/
int preprocess(char *input_file, char *output_file);

#endif /* !COMPILE_H */
