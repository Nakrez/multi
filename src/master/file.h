/**
 * @brief Handle a file to send to a deamon
 * @date 13/04/2013
 * @authors Baptiste COVOLATO <b.covolato@gmail.com>
 */

#ifndef MASTER_FILE_H
# define MASTER_FILE_H

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
    char *input_file;

    /**
     * @brief  Temp name associated to this file (for preprocess and reception
               of the object file)
     */
    char *output_file;

    /* It langage */
    e_language language;
} multi_file;

// FIXME : DOC PARAMS
/**
** @brief Run preprocess if needed
**
** @return 0 if everything worked well, -1 else
*/
int preprocess(multi_file *file);

/* FIXME : Add DOC */
void destroy_file(multi_file **file);

// FIXME : Add Doc
multi_file *new_file();

#endif /* !MASTER_FILE_H */
