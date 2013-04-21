#include <master/arg.h>

static int is_source(char *src)
{
    int len = strlen(src);

    if (len < 3)
        return 0;

    return src[0] != '-' && !strcmp(src + len - 2, ".c");
}

static char *requested_compiler()
{
    char *compile = getenv("MULTI_COMPILER");

    if (compile)
        return compile;

    return "gcc";
}
/*
 * TODO : handle -h|--help
 */
config_t *process_args(int argc, char *argv[])
{
    config_t *config = NULL;

    int c_opt_detected = 0;

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
        else if (!strcmp(argv[i], "-E"))
            config->local = 1;
        else if (!strcmp(argv[i], "-c"))
            c_opt_detected = 1;
    }

    if (!c_opt_detected)
        config->local = 1;

    argv[0] = requested_compiler();

    /*
     * Store arg (easier since config is already passed as argument
     * everywhere)
     */
    config->argv = argv;
    config->argc = argc;

    return config;
}
