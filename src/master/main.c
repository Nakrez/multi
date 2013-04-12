#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#include <master/file.h>

#define IP "192.168.0.28"
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

    char buffer[1024];

    multi_file *to_transmit = open_file("test.c");
    FILE *file_buf = NULL;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
        error("ERROR opening socket\n");

    server = gethostbyname(IP);

    if (server == NULL)
        error("ERROR, no such host\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr_list[0],
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(socket_fd,
        (struct sockaddr *)&serv_addr,
        sizeof(serv_addr)) < 0)
        error("ERROR connecting\n");
    else
        printf("client connected\n");

    if ((file_buf = fopen(to_transmit->temp_name, "r")) == NULL)
    {
        error("Cant open temp");
        close(socket_fd);
    }

    while (fread(buffer, 1, 1024, file_buf) > 0)
    {
        n = write(socket_fd, buffer, strlen(buffer));
    }

    fclose(file_buf);
    close(socket_fd);

    return 0;
}
