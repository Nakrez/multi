#include <master/config.h>

config_t *config_new()
{
    config_t *config = NULL;

    if ((config = malloc(sizeof (config_t))) == NULL)
        return NULL;

    if ((config->file = multi_file_new()) == NULL)
        config_free(&config);

    config->result = NULL;
    config->socket_fd = -1;
    config->argc = 0;
    config->argv = NULL;
    config->local = 0;
    config->nb_server = 0;
    config->servers = NULL;

    return config;
}

void config_free(config_t **config)
{
    if (*config)
    {
        multi_file_free(&(*config)->file);

        compile_result_free(&(*config)->result);

        if ((*config)->socket_fd > -1)
            close((*config)->socket_fd);

        free(*config);
        *config = NULL;
    }
}
