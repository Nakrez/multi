#include <share/arg.h>

static int argv_size_concate(int argc, char **argv)
{
    int result = 0;

    for (int i = 0; i < argc; ++i)
        result += strlen(argv[i]) + 1;

    return result;
}

char **dup_argv(int argc, char **argv)
{
    char **new_argv = NULL;

    if ((new_argv = malloc(argc * sizeof (char *))) == NULL)
        return NULL;

    /*
    * No deep copy is needed in multi so no need to waste time with
    * allocation and copy just remember to not free the content of the
    * new argv
    */
    for (int i = 0; i < argc; ++i)
        new_argv[i] = argv[i];

    return new_argv;
}

void add_argv(int argc, char ***argv, char *str)
{
    *argv = realloc(*argv, (argc + 1) * sizeof (char *));

    (*argv)[argc] = str;
}

int concate_argv(int argc, char **argv, char **result)
{
    int size;
    int size_arg = 0;
    int pos = 0;

    size = argv_size_concate(argc, argv);

    /* TODO Handle error */
    *result = malloc(size);

    for (int i = 0; i < argc; ++i)
    {
        size_arg = strlen(argv[i]);
        /* strncpy */
        strncpy(*result + pos, argv[i], size_arg);
        pos += size_arg;

        (*result)[pos++] = ' ';
    }

    (*result)[pos - 1] = 0;

    return size;
}
