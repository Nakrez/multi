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
} process_file;

int process_received_file(process_file *file);
void destroy_file(process_file **file);
process_file *allocate();

#endif /* !FILE_H */
