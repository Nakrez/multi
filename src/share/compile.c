#include <share/compile.h>

int preprocess(char *input_file, char *output_file)
{
    int status = 0;

    pid_t pid;

    if ((pid = fork()) < 0)
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

static void *close_pipe(int pipe_fd[2])
{
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return NULL;
}

/* FIXME : buf somewhere */
static void setup_gcc_arg(char *tab[],
                          char *str,
                          char *input_file,
                          char *output_file)
{
    int pos = 2;
    char *base = str;

    tab[0] = "gcc";
    tab[1] = "-fpreprocessed";

    if (str)
    {
        while (*str)
        {
            if (*str == ' ')
            {
                *str = 0;
                tab[pos++] = base;
                base = str + 1;
            }

            ++str;
        }
    }

    tab[pos] = "-c";
    tab[pos + 1] = input_file;
    tab[pos + 2] = "-o";
    tab[pos + 3] = output_file;
    tab[pos + 4] = NULL;
}

compile_result_t *compile_without_preprocess(char *input_file,
                                             char *output_file,
                                             char *argv)
{
    /* TODO : build compile_result_t and return it */
    int status;
    int std_out[2];
    int std_err[2];

    char *argv_splited[7 + count_occurence(argv, ' ')];

    pid_t pid;

    compile_result_t *result = NULL;

    if (pipe(std_out))
        return NULL;

    if (pipe(std_err))
        return close_pipe(std_out);

    if ((pid = fork()) < 0)
    {
        printf("Fork error");
        close_pipe(std_err);
        return close_pipe(std_out);
    }

    result = compile_result_new();
    setup_gcc_arg(argv_splited, argv, input_file, output_file);

    if (pid) /* Father */
    {
        close(std_out[1]);
        close(std_err[1]);

        waitpid(pid, &status, 0);

        result->std_out = read_fd(std_out[0]);
        result->std_err = read_fd(std_err[0]);

        close(std_out[0]);
        close(std_err[0]);
    }
    else /* Child */
    {
        close(std_out[0]);
        close(std_err[0]);

        dup2(std_out[1], STDOUT_FILENO);
        dup2(std_err[1], STDERR_FILENO);

        execvp("gcc", argv_splited);
    }

    result->status = WEXITSTATUS(status);

    return result;
}

compile_result_t *compile_result_new()
{
    compile_result_t *res = NULL;

    if ((res = malloc(sizeof (compile_result_t))) == NULL)
        return NULL;

    res->std_out = NULL;
    res->std_err = NULL;
    res->status = -1;

    return res;
}

void compile_result_free(compile_result_t **res)
{
    free((*res)->std_out);
    free((*res)->std_err);
    free(*res);

    *res = NULL;
}
