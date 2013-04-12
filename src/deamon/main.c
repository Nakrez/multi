#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#define IP "192.168.0.28"
#define PORT 4242

void error(const char* msg)
{
    printf(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;

    int socket_fd;
    int cli_fd;
    int n;

    socklen_t clilen;

    char buffer[1024];

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
        error("ERROR opening socket");

    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = 0;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;

    if (bind(socket_fd,
             (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) == -1)
        error("ERROR binding socket");

    listen(socket_fd,5);

    clilen = sizeof(cli_addr);
    cli_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, &clilen);

    if (cli_fd < 0)
        error("ERROR on accept");


    while((n = read(cli_fd, buffer, 1024)) > 0)
        printf("%s", buffer);

    if (n < 0)
        error("ERROR reading from socket");

    printf("Here is the message: %s\n", buffer);
    n = write(cli_fd, "OK", 2);

    if (n < 0)
        error("ERROR writing to socket");

    close(socket_fd);
    close(cli_fd);

    return 0;
}
