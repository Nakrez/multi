/**
** @file src/share/socket.h
** @brief All socket transmission related function
** @date 04/13/2013
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

#ifndef SOCKET_H
# define SOCKET_H

# include <unistd.h>

# include <stdio.h>
# include <netdb.h>
# include <strings.h>

# include <sys/types.h>
# include <sys/socket.h>

# include <netinet/in.h>

# include <share/error.h>
# include <share/config.h>
# include <share/compile.h>
# include <share/arg.h>

/**
** @brief Send a file to a file descriptor (can be socket or file)
**
** @param socket_fd     The fd to which you want to send your file
                        (used in @a multi with socket fd but can be file fd)
** @param input_name    The name of the file you want to send
**
** @return              0 if everything went well
                        -1 if the @a input_file can not be opened
                        -2 if a write error happened
*/
int send_file(int socket_fd, const char *input_name);

/**
** @brief Receive a file from a file descriptor (can be socket or file)
**
** @param socket_fd     The fd from which you want to read the file
                        (used in @a multi with socket fd but can be file fd)
** @param output_name   The path where you want to save the received file
**
** @return              0 if everything went well
                        -1 if the @a output_file can not be opened
                        -2 if a read error happened
*/
int recv_file(int socket_fd, const char *output_name);

/**
** @brief Initialise a socket for the @a multi server
**
** @param port  The port where you want to bind your socket
**
** @return      The socket fd if everything went well
                -1 else
*/
int create_server_socket(int port);

/**
** @brief Initialise a socket connection with a server
**
** @param   addr    The address of the server
** @param   port    The port of the server
**
** @return  The fd of the socket connection with the server
            -1 if it failed
*/
int create_client_socket(const char *addr, int port);

/**
 */

/**
** @brief Send the result of the compilation to a file descriptor
**        Compilation result only include compile stdout, stderr and exit
**        status. File resulting of compilation will eventually be sent after
**        but not handled by @a send_compile_result
**
** @param   fd      The file descriptor to which you want to send the
                    compilation result
** @param   result  The compilation result you want to send
**
** @return          0 if everything went well, -1 else
*/
int send_compile_result(int fd, compile_result_t *result);

/**
** @brief Receive the result of a compilation from a file descriptor
**        Compilation result only include compile stdout, stderr and exit
**        status. File resulting of compilation will eventually be sent after
**        but not handled by @a send_compile_result
**
** @param   fd  The file descriptor where @a recv_compile_result will read
**              the compilation result
**
** @return  The compilation result if everything went well, NULL else
*/
compile_result_t *recv_compile_result(int fd);

int send_argv(int fd, int argc, char **argv);

int recv_argv(int fd, int *argc, char ***argv);

#endif /* !SOCKET_H */
