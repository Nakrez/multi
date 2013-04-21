#include <master/client.h>

config_t *config;

/* #define IP "88.176.106.132" */
# define IP "127.0.0.1"

/* FIXME doc */
static int client_preprocess()
{
    if (preprocess(config->argc, config->argv))
    {
        config_free(&config);
        return 1;
    }

    /* TODO : Handle errors */
    send_argv(config->socket_fd, config->argc, config->argv);

    if (send_file(config->socket_fd, config->file->output_file) < 0)
    {
        ERROR_MSG("Error: Can not send file to the server\n");
        close(config->socket_fd);

        full_compilation(config->argc, config->argv);

        /* Never reached */
    }

    return 0;
}

/* FIXME doc */
static int client_retrieve_data()
{
    if ((config->result = recv_compile_result(config->socket_fd)) == NULL)
    {
        ERROR_MSG("Error: Can not receive compiler state from the server\n");
        close(config->socket_fd);

        full_compilation(config->argc, config->argv);
    }

    if (!config->result->status)
    {
        if (recv_file(config->socket_fd, config->file->output_file) < 0)
        {
            ERROR_MSG("Error: Can not receive compiled file from the server\n");
            close(config->socket_fd);

            full_compilation(config->argc, config->argv);

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
static int core_client()
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

static void broken_pipe_handler()
{
    printf("[multi] Server shut the connection down\n");

    full_compilation(config->argc, config->argv);
}

int launch_client(int argc, char *argv[])
{
    /* Error on processing arguments */
    if ((config = process_args(argc, argv)) == NULL)
        return 1;

    /* Local compilation needed */
    if (config->local)
        full_compilation(config->argc, config->argv);

    if (signal(SIGPIPE, broken_pipe_handler) == SIG_ERR)
    {
        /* TODO : ERROR HANDLING */
    }

    if (!config->file->input_file || !config->file->output_file)
        full_compilation(config->argc, config->argv);

    if ((config->socket_fd = create_client_socket(IP, get_port())) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");

        full_compilation(config->argc, config->argv);

        /* Return will be ignored since compiler will remplace multi */
        return 1;
    }

    /* Process file with server */
    return core_client(config);
}
