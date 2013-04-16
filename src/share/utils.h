/**
** @file src/share/utils.h
** @brief Function that are usefull but related to no specific part of multi
** @date 04/16/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
*/

#ifndef SHARE_UTILS_H
# define SHARE_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <linux/limits.h>

/* FIXME doc */
unsigned zero_strlen(char *str);

/* FIXME doc */
int neg_strlen(const char *str);

/* FIXME doc */
char *read_fd(int fd);

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
