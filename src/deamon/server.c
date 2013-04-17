#include <deamon/server.h>

// FIXME : Read in a configuration file
# define LOG_FILE "/home/zerkan/multi_server.log"

pthread_mutex_t server_mutex;
config_t *server_config = NULL;

/* FIXME doc */
static void *end_thread(thread_state_t **state)
{
    thread_state_free(state);

    DECR_SERVER_LOAD;

    return NULL;
}

/* FIXME doc */
static int set_timeout(int socket_fd)
{
    struct timeval timeout;

    /* FIXME Define timeout */
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                   sizeof(timeout)) < 0)
    {
        ERROR_MSG("Error: Can not set timeout on socket\n");

        return -1;
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                   sizeof(timeout)) < 0)
    {
        ERROR_MSG("Error: Can not set timeout on socket\n");

        return -2;
    }

    return 0;
}

/* FIXME doc */
static void *compile_file(void *state)
{
    thread_state_t *thread_state = (thread_state_t *)state;

    process_file_t *file = NULL;

    if (set_timeout(thread_state->cli_fd) < 0)
        goto exit_thread;

    file = process_file_new();

    /* TODO : clean it */
    int argv_size = 0;
    int pos = 0;
    int n = 0;

    read(thread_state->cli_fd, (char *)&argv_size, sizeof (int));

    if (argv_size)
    {
        file->argv = malloc(argv_size + 1);

        while ((n = read(thread_state->cli_fd, file->argv + pos,
                         argv_size - pos)) > 0)
            pos += n;

        file->argv[pos] = 0;
    }
    /* End TODO */

    if (recv_file(thread_state->cli_fd, file->input_name) < 0)
        goto exit_thread;

    file->result = compile_without_preprocess(file->input_name,
                                              file->output_name,
                                              file->argv);

    if (!file->result)
        goto exit_thread;

    /* FIXME handle error */
    send_compile_result(thread_state->cli_fd, file->result);

    if (!file->result->status)
    {
        if (send_file(thread_state->cli_fd, file->output_name) < 0)
            goto exit_thread;
    }

exit_thread:
    if (file)
        process_file_free(&file);

    return end_thread(&thread_state);
}

/* FIXME doc */
static int check_overload()
{
    int ret_value = 0;

    pthread_mutex_lock(&server_mutex);
    printf("Server load : %d/%d\n",
            server_config->server_load,
            server_config->max_load);

    /* If server overload close connection */
    if (server_config->server_load >= server_config->max_load)
        ret_value = -1;

    pthread_mutex_unlock(&server_mutex);

    return ret_value;
}

int server_start()
{
    thread_state_t *state = NULL;

    struct sockaddr_in cli_addr;

    int cli_fd;
    socklen_t clilen = sizeof (cli_addr);


    /* Allocate new configuration */
    if ((server_config = config_new()) == NULL)
    {
        ERROR_MSG("Internal error: Can not allocate configuration\n");
        return 1;
    }

    /* Creating socket */
    if ((server_config->socket_fd = create_server_socket(MULTI_PORT)) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");
        config_free(&server_config);
        return 1;
    }

    while (1)
    {
        cli_fd = accept(server_config->socket_fd, (struct sockaddr *)&cli_addr,
                        &clilen);

        if (cli_fd < 0)
        {
            ERROR_MSG("ERROR on accept\n");
            continue;
        }

        if (check_overload() < 0)
        {
            close(cli_fd);
            continue;
        }

        state = thread_state_new();

        state->cli_fd = cli_fd;

        INCR_SERVER_LOAD;

        pthread_create(&(state->thread), NULL, compile_file, state);
    }

    config_free(&server_config);

    return 0;
}
