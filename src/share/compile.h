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
# include <string.h>

# include <linux/limits.h>

# include <sys/wait.h>
# include <sys/types.h>

# include <share/error.h>

/**
** @brief Represent the output of the compiler
*/
typedef struct
{
    /**
    ** @brief The standard output of the compiler
    */
    char *std_out;

    /**
    ** @brief The standard error output of the compiler
    */
    char *std_err;

    /**
    ** @brief The exit code of the compiler
    */
    int status;
} compile_result_t;

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

/* FIXME add doc */
void full_compilation(char *input_file, char *output_file);

/* FIXME doc */
compile_result_t *compile_without_preprocess(char *input_file,
                                             char *output_file);

/**
** @brief Allocate a new compile_result structure
**
** @return  The allocated compile_result structure if everything went well
**          NULL else
*/
compile_result_t *compile_result_new();

/**
** @brief Free a compile_result structure allocate with @a compile_result_new()
**
** @param   res The compile_result structure you want to free
*/
void compile_result_free(compile_result_t **res);

#endif /* !COMPILE_H */
