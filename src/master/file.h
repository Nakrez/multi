/**
 * @brief Handle a file to send to a deamon
 * @date 13/04/2013
 * @authors Baptiste COVOLATO <b.covolato@gmail.com>
 */

#ifndef FILE_H
# define FILE_H

# include <unistd.h>

# include <stdlib.h>
# include <stdio.h>

# include <string.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>

# include <share/language.h>

typedef struct s_file
{
    /* The name of the file */
    char *file_name;

    /**
     * @brief  Temp name associated to this file (for preprocess and reception
               of the object file)
     */
    char *temp_name;

    /* It langage */
    e_language language;
} multi_file;

void destroy_file(multi_file **file);
multi_file *open_file(const char *file_name);

#endif /* !FILE_H */
