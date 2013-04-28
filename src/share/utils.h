/**
** @file src/share/utils.h
** @brief Function that are usefull but related to no specific part of multi
** @date 04/16/2013
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

#ifndef SHARE_UTILS_H
# define SHARE_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <linux/limits.h>

/* FIXME doc */
unsigned count_occurence(char *str, char c);

/* FIXME doc */
unsigned zero_strlen(char *str);

/* FIXME doc */
int neg_strlen(const char *str);

/* FIXME doc */
int read_fd(int fd, int size, char **buf);

/* FIXME doc */
char *read_all_fd(int fd);

/**
** @brief Write buffer @a data of size @a n in a file descriptor @a fd
**
** @param fd    The file descriptor where you want to write @a data
** @param data  The data you want to write in @a fd
** @param n     The size in byte you want to write in @a fd
**
** @return      0 if everything went well
                -1 else
*/
int write_to_fd(int fd, const char *data, size_t n);

#endif /* !SHARE_UTILS_H */
