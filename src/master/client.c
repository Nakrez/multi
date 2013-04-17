#include <master/client.h>

/* #define IP "88.176.106.132" */
# define IP "127.0.0.1"

/* FIXME doc */
static int client_preprocess(config_t *config)
{
    int argv_len = zero_strlen(config->argv);

    if (preprocess(config->argv))
    {
        config_free(&config);
        return 1;
    }

    /* TODO : Handle errors */
    write_to_fd(config->socket_fd, (char *)&argv_len, sizeof (int));

    if (config->argv)
        write_to_fd(config->socket_fd, config->argv, strlen(config->argv));

    if (send_file(config->socket_fd, config->file->output_file) < 0)
    {
        ERROR_MSG("Error: Can not send file to the server\n");
        close(config->socket_fd);

        full_compilation(config->argv);

        /* Never reached */
    }

    return 0;
}

/* FIXME doc */
static int client_retrieve_data(config_t *config)
{
    if ((config->result = recv_compile_result(config->socket_fd)) == NULL)
    {
        ERROR_MSG("Error: Can not receive compiler state from the server\n");
        close(config->socket_fd);

        full_compilation(config->argv);
    }

    if (!config->result->status)
    {
        if (recv_file(config->socket_fd, config->file->output_file) < 0)
        {
            ERROR_MSG("Error: Can not receive compiled file from the server\n");
            close(config->socket_fd);

            full_compilation(config->argv);

            /* Never reached */
        }
    }

    return 0;
}

/* FIXME doc */
static void print_compile_result(compile_result_t *result)
{
    if (result->std_out)
        fprintf(stdout, result->std_out);

    if (result->std_err)
        fprintf(stderr, result->std_err);
}

/* FIXME doc */
static int core_client(config_t *config)
{
    int return_value = 0;

    /* Preprocess the file and send it to the server */
    if (client_preprocess(config))
        return 1;

    /* Retrieve object file from server */
    if (client_retrieve_data(config))
        return 1;

    print_compile_result(config->result);

    return_value = config->result->status;

    config_free(&config);

    return return_value;
}

int launch_client(int argc, char *argv[])
{
    config_t *config;

    /* Error on processing arguments */
    if ((config = process_args(argc, argv)) == NULL)
        return 1;

    if (!config->file->input_file || !config->file->output_file)
        full_compilation(config->argv);

    if ((config->socket_fd = create_client_socket(IP, MULTI_PORT)) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");

        full_compilation(config->argv);

        /* Return will be ignored since compiler will remplace multi */
        return 1;
    }

    /* Process file with server */
    return core_client(config);
}
