/**
 * @brief Handle a file to send to a deamon
 * @date 13/04/2013
 * @authors Baptiste COVOLATO <b.covolato@gmail.com>
 */

#ifndef MASTER_FILE_H
# define MASTER_FILE_H

# include <stdlib.h>

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
} multi_file_t;

/**
** @brief Allocate a new client file
**
** @return  The allocated file if everything went well
            NULL else
*/
multi_file_t *multi_file_new();

/**
** @brief   Free a client file and set it to NULL allocate with
            @a multi_file_new()
**
** @param   file    The file you want to free
*/
void multi_file_free(multi_file_t **file);

#endif /* !MASTER_FILE_H */
