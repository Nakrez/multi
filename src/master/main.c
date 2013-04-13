#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include <netinet/in.h>

#include <fcntl.h>
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
    int read_bytes = 1;
    int portno = PORT;

    FILE* file;

    char buf[1024];

    multi_file *to_transmit = open_file("test.c");

    if (to_transmit == NULL)
        error("Transmit file error");

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

    if ((file = fopen(to_transmit->temp_name, "r")) == NULL)
    {
        error("Cant open temp");
        close(socket_fd);
    }

    while (read_bytes)
    {
        read_bytes = fread(buf, 1, 1024, file);
        send(socket_fd, buf, read_bytes, 0);
    }

    fclose(file);
    close(socket_fd);

    return 0;
}
