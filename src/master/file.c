#include <master/file.h>

/**
 * @brief Run preprocess if needed
 * @param filename      The file of the input file
 * @param result_name   The temporary file where to put the preprocess result
 *
 * @return 0 if everything worked well, -1 else
 */
int preprocess(multi_file *file)
{
    int status = 0;

    pid_t pid = fork();

    if (pid < 0)
        return -1;

    if (pid)
        waitpid(pid, &status, 0);
    else
    {
        char *argv[] =
        {
            "gcc",
            "-E",
            file->input_file,
            "-o",
            file->output_file,
            NULL
        };

        execvp("gcc", argv);
    }

    return WEXITSTATUS(status) == 0;
}

multi_file *new_file()
{
    multi_file *file = NULL;

    if ((file = malloc(sizeof(multi_file))) == NULL)
        return NULL;

    file->input_file = NULL;
    file->output_file = NULL;

    return file;
}

void destroy_file(multi_file **file)
{
    free((*file)->input_file);
    free((*file)->output_file);

    free(*file);

    *file = NULL;
}
