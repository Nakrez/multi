#include <deamon/config.h>

config_t *config_new()
{
    config_t *config = NULL;

    if ((config = malloc(sizeof (config_t))) == NULL)
        return NULL;

    config->server_load = 0;
    config->max_load = THREAD_COMPILE_MAX;
    config->thread_pool = malloc(config->max_load * sizeof (pthread_t));

    if (config->thread_pool == NULL)
        config_free(&config);

    return config;
}

void config_free(config_t **config)
{
    free((*config)->thread_pool);
    free(*config);

    *config = NULL;
}
