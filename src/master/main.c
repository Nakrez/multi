#include <unistd.h>

#include <stdio.h>

#include <master/usage.h>
#include <master/arg.h>

#include <share/socket.h>

#define IP "88.176.106.132"

int main(int argc, char *argv[])
{
    int socket_fd;

    config_t *config;

    if (argc < 5)
    {
        usage();
        return 0;
    }

    /* Error on processing arguments */
    if ((config = process_args(argc, argv)) == NULL)
        return 1;

    socket_fd = create_client_socket(IP, MULTI_PORT);

    if (socket_fd < 0)
        return 1;

    send_file(socket_fd, config->file->input_file);

    printf("File sent waiting for response\n");

    recv_file(socket_fd, config->file->output_file);

    destroy_config(&config);
    close(socket_fd);

    return 0;
}
