/**
** @file src/deamon/server.h
** @brief Main functions of server
** @date 04/14/2013
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

#ifndef SERVER_H
# define SERVER_H

# include <sys/time.h>

# include <share/compile.h>
# include <share/socket.h>
# include <share/error.h>

# include <deamon/config.h>
# include <deamon/file.h>

// FIXME : Doc
int server_start();

# define INCR_SERVER_LOAD                                   \
    do                                                      \
    {                                                       \
        pthread_mutex_lock(&server_mutex);                  \
        ++(server_config->server_load);                     \
        pthread_mutex_unlock(&server_mutex);                \
    } while (0)

# define DECR_SERVER_LOAD                                   \
    do                                                      \
    {                                                       \
        pthread_mutex_lock(&server_mutex);                  \
        --(server_config->server_load);                     \
        pthread_mutex_unlock(&server_mutex);                \
    } while (0)

#endif /* !SERVER_H */
