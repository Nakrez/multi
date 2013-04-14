#include <share/compile.h>

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
