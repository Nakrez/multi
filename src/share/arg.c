#include <share/arg.h>

/* TODO : Same code in master/arg.c clean it */
static int is_source(char *src)
{
    int len = strlen(src);

    if (len < 3)
        return 0;

    return src[0] != '-' &&
           ((len > 2 && !strcmp(src + len - 2, ".c")) ||
           (len > 3 && !strcmp(src + len - 3, ".cc")) ||
           (len > 4 && !strcmp(src + len - 4, ".cpp")));
}
/* END TODO*/

/**
** @brief Give the length of concatenation of argv array
**
** @param   argc    The number of arguments
** @param   argv    The array containing the arguments
**
** @return          The result size
*/
static int argv_size_concate(int argc, char **argv)
{
    int result = 0;

    /* +1 for the separating space or the final \0 */
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

int add_argv(int argc, char ***argv, char *str)
{
    if ((*argv = realloc(*argv, (argc + 1) * sizeof (char *))) == NULL)
        return -1;

    (*argv)[argc] = str;

    return 0;
}

int concate_argv(int argc, char **argv, char **result)
{
    int size;
    int size_arg = 0;
    int pos = 0;

    size = argv_size_concate(argc, argv);

    if ((*result = malloc(size)) == NULL)
        return -1;

    for (int i = 0; i < argc; ++i)
    {
        size_arg = strlen(argv[i]);
        strncpy(*result + pos, argv[i], size_arg);
        pos += size_arg;

        (*result)[pos++] = ' ';
    }

    (*result)[pos - 1] = 0;

    return size;
}
int split_argv(char *argv, char ***result)
{
    int old = -1;
    int new = 0;
    int i = 0;
    int argc = count_occurence(argv, ' ') + 1;

    char *temp = argv;

    /* TODO Handle errors */
    *result = malloc((argc + 1) * sizeof (char *));

    while (1)
    {
        if (*temp == ' ' || !*temp)
        {
            /* TODO Handle errors */
            (*result)[i] = malloc(new - old);
            strncpy((*result)[i], argv + old + 1, new - old);
            (*result)[i][new - old - 1] = 0;

            ++i;

            if (!*temp)
                break;

            old = new;
        }
        ++temp;
        ++new;
    }

    (*result)[i] = NULL;

    return argc;
}

void update_argv_file(int argc, char **argv, char *input_file, char *output_file)
{
    for (int i = 0; i < argc; ++i)
    {
        if (is_source(argv[i]))
        {
            free(argv[i]);
            argv[i] = input_file;
        }
        if (i > 0 && !strcmp(argv[i - 1], "-o"))
        {
            free(argv[i]);
            argv[i] = output_file;
        }
    }
}
