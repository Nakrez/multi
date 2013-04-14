#include <master/client.h>

/* #define IP "88.176.106.132" */
# define IP "127.0.0.1"

int launch_client(int argc, char *argv[])
{
    config_t *config;

    /* Error on processing arguments */
    if ((config = process_args(argc, argv)) == NULL)
        return 1;

    if ((config->socket_fd = create_client_socket(IP, MULTI_PORT)) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");

        full_compilation(config->file->input_file, config->file->output_file);

        /* Return will be ignored since compiler will remplace multi */
        return 1;
    }

    printf("Preprocessing file %s\n", config->file->input_file);

    if (!preprocess(config->file->input_file, config->file->output_file))
        goto exit;

    printf("Preprocessing done\n");

    printf("Sending file to server for compilation\n");

    if (send_file(config->socket_fd, config->file->output_file) < 0)
    {
        ERROR_MSG("Error: Can not send file to the server\n");
        close(config->socket_fd);

        full_compilation(config->file->input_file, config->file->output_file);

        /* Never reached */
    }

    printf("File sent waiting for response\n");

    if (recv_file(config->socket_fd, config->file->output_file) < 0)
    {
        ERROR_MSG("Error: Can not receive compiled file from the server\n");
        close(config->socket_fd);

        full_compilation(config->file->input_file, config->file->output_file);

        /* Never reached */
    }

    printf("File received\n");

exit:
    config_free(&config);

    return 0;
}
