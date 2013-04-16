#include <master/client.h>

/* #define IP "88.176.106.132" */
# define IP "127.0.0.1"

/* FIXME doc */
static int client_preprocess(config_t *config)
{

    printf("Preprocessing file %s\n", config->file->input_file);

    if (preprocess(config->file->input_file, config->file->output_file))
    {
        config_free(&config);
        return 1;
    }

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

    return 0;
}

/* FIXME doc */
static int client_retrieve_data(config_t *config)
{
    /* FIXME handle error and desalocation */
    config->result = recv_compile_result(config->socket_fd);

    if (recv_file(config->socket_fd, config->file->output_file) < 0)
    {
        ERROR_MSG("Error: Can not receive compiled file from the server\n");
        close(config->socket_fd);

        full_compilation(config->file->input_file, config->file->output_file);

        /* Never reached */
    }

    printf("File received\n");

    return 0;
}

/* FIXME doc */
static int core_client(config_t *config)
{
    /* Preprocess the file and send it to the server */
    if (client_preprocess(config))
        return 1;

    /* Retrieve object file from server */
    if (client_retrieve_data(config))
        return 1;

    config_free(&config);

    return 0;
}

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

    /* Process file with server */
    return core_client(config);
}
