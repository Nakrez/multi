#include <share/compile.h>

/* FIXME add doc */
int preprocess(char *input_file, char *output_file)
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
            input_file,
            "-o",
            output_file,
            NULL
        };

        execvp("gcc", argv);
    }

    return WEXITSTATUS(status);
}

void full_compilation(char *input_file, char *output_file)
{
    ERROR_MSG("Invoking gcc -c %s -o %s\n", input_file, output_file);

    char *argv[] =
    {
        "gcc",
        "-c",
        input_file,
        "-o",
        output_file,
        NULL
    };

    execvp("gcc", argv);
}

int compile_without_preprocess(char *input_file, char *output_file)
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
            input_file,
            "-o",
            output_file,
            NULL
        };

        execvp("gcc", argv);
    }

    return WEXITSTATUS(status) == 0;
}

