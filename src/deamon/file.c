#include <deamon/file.h>

int process_received_file(process_file *file)
{
    int status;

    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork error");
        return -1;
    }

    if (pid)
        waitpid(pid, &status, 0);
    else
    {
        char *argv[] =
        {
            "gcc",
            "-fpreprocessed",
            "-c",
            file->input_name,
            "-o",
            file->output_name,
            NULL
        };

        execvp("gcc", argv);
    }

    return WEXITSTATUS(status) == 0;
}

void destroy_file(process_file **file)
{
    if (!*file)
        return;

    if ((*file)->input_name)
        free((*file)->input_name);

    free(*file);
    *file = NULL;
}

process_file *allocate()
{
    char *tmp = NULL;

    process_file *file = NULL;

    if ((file = malloc(sizeof (process_file))) == NULL)
        return NULL;

    if ((file->input_name = tmpnam(NULL)) == NULL)
    {
        destroy_file(&file);
        return NULL;
    }

    tmp = calloc(strlen (file->input_name) + 3, 1);

    sprintf(tmp, "%s.c", file->input_name);

    file->input_name = tmp;

    if ((file->output_name = tmpnam(NULL)) == NULL)
    {
        destroy_file(&file);
        return NULL;
    }

    return file;
}
