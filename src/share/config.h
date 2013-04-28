/**
** @file src/share/config.h
** @brief Multi internal configuration file
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

#ifndef SHARE_CONFIG_H
# define SHARE_CONFIG_H

# include <unistd.h>
# include <stdlib.h>

/* The size of the queue of the server */
# define SOCKET_QUEUE 5

/* The port Multi use */
# define DEFAULT_MULTI_PORT 8216

# define DEFAULT_MULTI_HOST "127.0.0.1"
/*
The number max of concurent compile unit accepted by a server
Limit : The number of core online
*/
# define THREAD_COMPILE_MAX sysconf(_SC_NPROCESSORS_ONLN)

# define MULTI_VERSION "1.0.0"

/**
** @brief Get the port multi (client or server) have to use
**
** @return The port to use
*/
int get_port();

/**
** @brief Get all server the client can connect
**
** @return all hosts separated by spaces
*/
char *get_hosts();

#endif /* !SHARE_CONFIG_H */
