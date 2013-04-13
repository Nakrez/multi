#ifndef SOCKET_H
# define SOCKET_H

# include <unistd.h>

# include <stdio.h>

# include <sys/socket.h>

int send_file(int socket_fd, const char *input_name);
int recv_file(int socket_fd, const char *output_name);

#endif /* !SOCKET_H */
