#include <master/config.h>

config_t *config_new()
{
    config_t *config = NULL;

    if ((config = malloc(sizeof (config_t))) == NULL)
        return NULL;

    if ((config->file = multi_file_new()) == NULL)
        config_free(&config);

    config->socket_fd = -1;

    return config;
}

void config_free(config_t **config)
{
    multi_file_free(&(*config)->file);

    if ((*config)->socket_fd > -1)
        close((*config)->socket_fd);

    free(*config);
    *config = NULL;
}
