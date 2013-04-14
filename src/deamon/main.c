#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <share/socket.h>

#include <deamon/file.h>

#define IP "192.168.0.28"
#define PORT 8216

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
    int yes = 1;

    socklen_t clilen;

    process_file *file = NULL;

    file = allocate();

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // FIXME TEST ERROR
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int));

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

    listen(socket_fd, 5);

    clilen = sizeof(cli_addr);
    cli_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, &clilen);

    if (cli_fd < 0)
        error("ERROR on accept");

    recv_file(cli_fd, file->input_name);

    printf("File received. Processing... \n");

    process_received_file(file);

    printf("File processed. Sending response...\n");

    send_file(cli_fd, file->output_name);

    printf("Transfer OK\n");

    destroy_file(&file);

    close(socket_fd);
    close(cli_fd);

    return 0;
}
