#include <master/arg.h>

/*
 * TODO : handle -h|--help
 * TODO : Optimize size of config->argv to avoid realloc
 */
config_t *process_args(int argc, char *argv[])
{
    /* -4 because -o FILE -c FILE */
    int compiler_args_end = argc - 4;
    int output_place = argc - 3;
    int input_place = argc - 1;
    int pos = 0;

    config_t *config = NULL;

    if ((config = config_new()) == NULL)
    {
        ERROR_MSG("Internal error: Can not allocate configuration\n");
        return NULL;
    }

    for (int i = 1; i < compiler_args_end; ++i)
    {
        /* + 2 for separating space and final '\0' */
        config->argv = realloc(config->argv, zero_strlen(config->argv) +
                               strlen(argv[i]) + 2);

        strcpy(config->argv + pos, argv[i]);

        pos += strlen(argv[i]);

        config->argv[pos] = ' ';
        config->argv[pos + 1] = 0;

        /* to handled added ' ' */
        ++pos;
    }

    // FIXME : Handle errors
    config->file->output_file = malloc(strlen(argv[output_place]) + 1);
    config->file->input_file = malloc(strlen(argv[input_place]) + 1);

    strcpy(config->file->input_file, argv[input_place]);
    strcpy(config->file->output_file, argv[output_place]);

    return config;
}
