/**
** @file src/deamon/file.h
** @brief Internal representation of files used by the deamon
** @date 04/13/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
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
