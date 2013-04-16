#include <master/arg.h>

config_t *process_args(int argc, char *argv[])
{
    /* -4 because -o FILE -c FILE */
    int compiler_args_end = argc - 4;
    int input_place = argc - 3;
    int output_place = argc - 1;

    config_t *config = NULL;

    if ((config = config_new()) == NULL)
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
    config->file->output_file = malloc(strlen(argv[output_place]) + 1);
    config->file->input_file = malloc(strlen(argv[input_place]) + 1);

    strcpy(config->file->input_file, argv[input_place]);
    strcpy(config->file->output_file, argv[output_place]);

    return config;
}
