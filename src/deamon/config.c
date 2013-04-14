#include <deamon/config.h>

config_t *config_new()
{
    config_t *config = NULL;

    if ((config = malloc(sizeof (config_t))) == NULL)
        return NULL;

    config->server_load = 0;
    config->max_load = THREAD_COMPILE_MAX;
    config->socket_fd = -1;

    return config;
}

void config_free(config_t **config)
{
    if ((*config)->socket_fd > -1)
        close((*config)->socket_fd);

    free(*config);

    *config = NULL;
}

thread_state_t *thread_state_new()
{
    thread_state_t *state = NULL;

    if ((state = malloc(sizeof (thread_state_t))) == NULL)
        return NULL;

    state->cli_fd = -1;

    return state;
}

void thread_state_free(thread_state_t **state)
{
    if ((*state)->cli_fd > -1)
        close((*state)->cli_fd);

    free(*state);

    *state = NULL;
}
