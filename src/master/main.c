#include <unistd.h>

#include <stdio.h>

#include <master/file.h>
#include <master/usage.h>

#include <share/socket.h>

#define IP "88.176.106.132"

int main(int argc, char *argv[])
{
    int socket_fd;

    if (argc < 5)
    {
        usage();
        return 0;
    }

    socket_fd = create_client_socket(IP, MULTI_PORT);

    if (socket_fd < 0)
        return 1;

    multi_file *to_transmit = open_file("test.c");

    if (to_transmit == NULL)
    {
        close(socket_fd);
        return 1;
    }

    send_file(socket_fd, to_transmit->temp_name);

    printf("File sent waiting for response\n");

    recv_file(socket_fd, to_transmit->temp_name);

    destroy_file(&to_transmit);
    close(socket_fd);

    return 0;
}
