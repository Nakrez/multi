/**
** @file src/deamon/file.h
** @brief Internal representation of files used by the deamon
** @date 04/13/2013
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

#ifndef FILE_H
# define FILE_H

# include <unistd.h>

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <sys/types.h>
# include <sys/wait.h>

# include <share/language.h>
# include <share/compile.h>

/**
** @brief The structure used to represent a file to compile by the deamon
*/
typedef struct
{
    /* The name of the input file (on server -> temporary file) */
    char *input_name;

    /* The name of the output file (on server -> temporary file) */
    char *output_name;

    /* The result of the compilation (return of the real compiler) */
    compile_result_t *result;

    /* The language of the file (not handle yet) */
    e_language langage;
} process_file_t;

/**
** @brief Allocate a deamon file
**
** @return The allocated structure
*/
process_file_t *process_file_new();

/**
** @brief Free the structure returns by @a process_file_new()
**
** @param   file    The structure you want to free
*/
void process_file_free(process_file_t **file);

#endif /* !FILE_H */
