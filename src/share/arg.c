#include <share/arg.h>

char **dup_argv(int argc, char **argv)
{
    char **new_argv = NULL;

    if ((new_argv = malloc(argc * sizeof (char *))) == NULL)
        return NULL;

    for (int i = 0; i < argc; ++i)
        /*
         * No deep copy is needed in multi so no need to waste time with
         * allocation and copy
         */
        new_argv[i] = argv[i];

    return new_argv;
}

void add_argv(int argc, char ***argv, char *str)
{
    *argv = realloc(*argv, (argc + 1) * sizeof (char *));

    (*argv)[argc] = str;
}
