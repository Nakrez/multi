#include <master/arg.h>

static config_t *new_config()
{
    config_t *config = NULL;

    if ((config = malloc(sizeof (config_t))) == NULL)
        return NULL;

    if ((config->file = new_file()) == NULL)
        destroy_config(&config);

    return config;
}

config_t *process_args(int argc, char *argv[])
{
    /* -4 because -o FILE -c FILE */
    int compiler_args_end = argc - 4;
    int input_place = argc - 3;
    int output_place = argc - 1;

    config_t *config = NULL;

    if ((config = new_config()) == NULL)
    {
        ERROR_MSG("Internal error: Can not allocate configuration\n");
        return NULL;
    }

    // TODO : Handle compiler args
    for (int i = 1; i < compiler_args_end; ++i)
    {
        printf("Compiler args : %s\n", argv[i]);
    }

    // FIXME : Handle errors
    config->file->input_file = malloc(strlen(argv[input_place]) + 1);
    config->file->output_file = malloc(strlen(argv[output_place]) + 1);

    strcpy(config->file->input_file, argv[input_place]);
    strcpy(config->file->output_file, argv[output_place]);

    return config;
}

void destroy_config(config_t **config)
{
    destroy_file(&(*config)->file);

    free(*config);
    *config = NULL;
}
