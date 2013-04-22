#include <master/arg.h>

static char *internal_cmp = NULL;

/* TODO : optimise it because extract_language does the same */
static int is_source(char *src)
{
    int len = strlen(src);

    if (len < 1)
        return 0;

    return src[0] != '-' &&
           ((len > 2 && !strcmp(src + len - 2, ".c")) ||
           (len > 3 && !strcmp(src + len - 3, ".cc")) ||
           (len > 4 && !strcmp(src + len - 4, ".cpp")));
}

static char *requested_compiler(e_language lang)
{
    char *compile = getenv("MULTI_COMPILER");

    /* If compiler set with --compiler option */
    if (internal_cmp)
        return internal_cmp;
    /* If compiler set by environnement */
    else if (compile)
        return compile;
    /* Auto detect compiler */
    else if (lang != UNKNOWN)
        return get_compiler(lang);

    return "gcc";
}
/*
 * TODO : handle --help
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

    if (argc > 3 && !strcmp(argv[1], "--compiler"))
    {
        internal_cmp = argv[2];
        argv += 2;
        argc -= 2;
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

    if (config->file->input_file)
        config->file->language = extract_language(config->file->input_file);

    argv[0] = requested_compiler(config->file->language);

    /*
     * Store arg (easier since config is already passed as argument
     * everywhere)
     */
    config->argv = argv;
    config->argc = argc;

    return config;
}
