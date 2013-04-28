/**
** @brief Handle a file to send to a deamon
** @date 13/04/2013
** @authors Baptiste COVOLATO <b.covolato@gmail.com>
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
