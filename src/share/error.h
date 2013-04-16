/**
** @date 04/14/2013
*/

#ifndef SHARE_ERROR_H
# define SHARE_ERROR_H

# include <stdio.h>

# define ERROR_MSG(...)                         \
    fprintf(stderr, __VA_ARGS__)

# define TREAT_ERROR(Cond)                      \
    if (Cond)                                   \
        goto error

#endif /* !SHARE_ERROR_H */
