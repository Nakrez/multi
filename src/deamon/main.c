#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <share/socket.h>
#include <share/config.h>

#include <deamon/file.h>
#include <deamon/usage.h>
#include <deamon/arg.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in cli_addr;

    int socket_fd;
    int cli_fd;

    switch (parse_arg(argc, argv))
    {
        case SERVER_USAGE:
            usage();
            return 0;
        case SERVER_START:
            printf("Option not handled yet\n");
            break;
        case SERVER_RESTART:
            printf("Option not handled yet\n");
            break;
        case SERVER_STOP:
            printf("Option not handled yet\n");
            break;
        case SERVER_PID:
            printf("Option not handled yet\n");
            break;
    }
    socklen_t clilen;

    process_file *file = NULL;

    socket_fd = create_server_socket(MULTI_PORT);

    /* If server can not initialise socket exit it */
    if (socket_fd < 0)
        return 1;

    clilen = sizeof(cli_addr);
    cli_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, &clilen);

    if (cli_fd < 0)
        ERROR_MSG("ERROR on accept\n");

    file = allocate();

    recv_file(cli_fd, file->input_name);

    printf("File received. Processing... \n");

    process_received_file(file);

    printf("File processed. Sending response...\n");

    send_file(cli_fd, file->output_name);

    printf("Transfer OK\n");

    destroy_file(&file);

    close(cli_fd);
    close(socket_fd);

    return 0;
}
