#include <share/compile.h>

int preprocess(int argc, char **argv)
{
    int status = 0;
    char **new_argv = NULL;

    pid_t pid;

    if ((pid = fork()) < 0)
        return -1;

    if (pid)
        waitpid(pid, &status, 0);
    else
    {
        new_argv = dup_argv(argc, argv);
        new_argv[0] = "gcc";

        add_argv(argc++, &new_argv, "-E");
        add_argv(argc++, &new_argv, NULL);

        execvp("gcc", new_argv);
    }

    return WEXITSTATUS(status);
}

void full_compilation(int argc, char **argv)
{
    char **new_argv = NULL;

    new_argv = dup_argv(argc, argv);
    new_argv[0] = "gcc";

    add_argv(argc++, &new_argv, NULL);

    execvp("gcc", new_argv);
}

static void *close_pipe(int pipe_fd[2])
{
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return NULL;
}

compile_result_t *compile_without_preprocess(int argc, char **argv)
{
    /* TODO : build compile_result_t and return it */
    int status;
    int std_out[2];
    int std_err[2];

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

    if (pid) /* Father */
    {
        close(std_out[1]);
        close(std_err[1]);

        waitpid(pid, &status, 0);

        result->std_out = read_all_fd(std_out[0]);
        result->std_err = read_all_fd(std_err[0]);

        close(std_out[0]);
        close(std_err[0]);
    }
    else /* Child */
    {
        char **new_argv = dup_argv(argc, argv);
        new_argv[0] = "gcc";

        add_argv(argc++, &new_argv, "-fpreprocessed");
        add_argv(argc++, &new_argv, NULL);

        close(std_out[0]);
        close(std_err[0]);

        dup2(std_out[1], STDOUT_FILENO);
        dup2(std_err[1], STDERR_FILENO);

        execvp("gcc", new_argv);
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
