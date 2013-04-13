#include <master/file.h>

/**
 * @brief Run preprocess if needed
 * @param filename      The file of the input file
 * @param result_name   The temporary file where to put the preprocess result
 *
 * @return 0 if everything worked well, -1 else
 */
static int preprocess(const char *filename, const char *result_name)
{
    int status = 0;

    pid_t pid = fork();

    if (pid < 0)
        return -1;

    if (pid)
        waitpid(pid, &status, 0);
    else
    {
        const char *const argv[] =
        {
            "gcc",
            "-E",
            filename,
            "-o",
            result_name,
            NULL
        };

        execvp("gcc", argv);
    }

    return WEXITSTATUS(status) == 0;
}

static multi_file *new_file()
{
    multi_file *file = NULL;

    if ((file = malloc(sizeof(multi_file))) == NULL)
        return NULL;

    file->file_name = NULL;
    file->temp_name = NULL;

    return file;
}

void destroy_file(multi_file **file)
{
    if ((*file)->file_name)
        free((*file)->file_name);

    free(*file);

    *file = NULL;
}

multi_file *open_file(const char *file_name)
{
    multi_file *file_return = NULL;

    /* Fail malloc */
    if ((file_return = new_file()) == NULL)
        return NULL;

    if ((file_return->file_name = malloc(strlen(file_name) + 1)) == NULL)
    {
        destroy_file(&file_return);
        return NULL;
    }

    strcpy(file_return->file_name, file_name);

    if ((file_return->temp_name = tmpnam(NULL)) == NULL)
    {
        destroy_file(&file_return);
        return NULL;
    }

    if (!preprocess(file_name, file_return->temp_name))
    {
        destroy_file(&file_return);
        return NULL;
    }

    return file_return;
}
