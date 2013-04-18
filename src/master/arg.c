#include <master/arg.h>

static int is_source(char *src)
{
    int len = strlen(src);

    if (len < 3)
        return 0;

    return src[0] != '-' && !strcmp(src + len - 2, ".c");
}

/*
 * TODO : handle -h|--help
 * TODO : Optimize size of config->argv to avoid realloc
 */
config_t *process_args(int argc, char *argv[])
{
    config_t *config = NULL;

    if ((config = config_new()) == NULL)
    {
        ERROR_MSG("Internal error: Can not allocate configuration\n");
        return NULL;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-o"))
            config->file->output_file = argv[++i];
        else if (is_source(argv[i]))
            config->file->input_file = argv[i];
    }

    /*
     * Store arg (easier since config is already passed as argument
     * everywhere)
     */
    config->argv = argv;
    config->argc = argc;

    return config;
}
