/**
** @file src/share/socket.h
** @brief All socket transmission related function
** @date 04/13/2013
** @author Baptiste COVOLATO <b.covolato@gmail.com>
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
*/
int create_client_socket(const char *addr, int port);

#endif /* !SOCKET_H */
