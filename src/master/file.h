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

// FIXME : Add Doc
multi_file_t *multi_file_new();

/* FIXME : Add DOC */
void multi_file_free(multi_file_t **file);

#endif /* !MASTER_FILE_H */
