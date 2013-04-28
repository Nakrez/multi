/**
** @file src/share/compile.h
** @brief All compilation related function
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

#ifndef COMPILE_H
# define COMPILE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <sys/wait.h>
# include <sys/types.h>

# include <share/error.h>
# include <share/utils.h>
# include <share/arg.h>

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
int preprocess(int argc, char **argv);

/* FIXME add doc */
void full_compilation(int argc, char **argv);

/* FIXME doc */
compile_result_t *compile_without_preprocess(int argc, char **argv);

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
