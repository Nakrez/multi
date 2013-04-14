#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


#include <share/socket.h>

#include <deamon/file.h>

#define PORT 8216

int main(int argc, char *argv[])
{
    struct sockaddr_in cli_addr;

    int socket_fd;
    int cli_fd;

    socklen_t clilen;

    process_file *file = NULL;

    file = allocate();

    socket_fd = create_server_socket(PORT);

    /* FIXME : Not proper exit */
    if (socket_fd < 0)
        return 1;

    clilen = sizeof(cli_addr);
    cli_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, &clilen);

    if (cli_fd < 0)
        ERROR_MSG("ERROR on accept\n");

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
