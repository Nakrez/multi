/**
** @date 04/13/2013
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

typedef struct
{
    char *input_name;

    char *output_name;

    e_language langage;
} process_file_t;

/* FIXME doc */
void process_file_free(process_file_t **file);

/* FIXME doc */
process_file_t *process_file_new();

#endif /* !FILE_H */
