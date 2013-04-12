#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#define IP "194.168.0.28"
#define PORT 4242

void error(const char *msg)
{
    printf(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    int socket_fd;
    int portno = PORT;
    int n;

    char buffer[256] = "Message send";

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
        error("ERROR opening socket");

    server = gethostbyname(IP);

    if (server == NULL)
        error("ERROR, no such host");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(socket_fd,
        (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    n = write(socket_fd, buffer, strlen(buffer));

    if (n < 0) 
         error("ERROR writing to socket");

    bzero(buffer,256);

    n = read(socket_fd, buffer, 255);

    if (n < 0) 
         error("ERROR reading from socket");

    printf("%s\n",buffer);

    close(socket_fd);

    return 0;
}
