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
#include <share/socket.h>

#define IP "88.176.106.132"
#define PORT 8216

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

    send_file(socket_fd, to_transmit->temp_name);

    printf("File sent waiting for response\n");

    recv_file(socket_fd, to_transmit->temp_name);

    destroy_file(&to_transmit);
    close(socket_fd);

    return 0;
}
