#include <deamon/file.h>

void process_file_free(process_file_t **file)
{
    if (!*file)
        return;

    /* Remove temprorary files */
    unlink((*file)->input_name);
    unlink((*file)->output_name);

    free((*file)->input_name);
    free((*file)->output_name);
    compile_result_free(&(*file)->result);

    free(*file);
    *file = NULL;
}

process_file_t *process_file_new()
{
    char *tmp = NULL;

    process_file_t *file = NULL;

    if ((file = malloc(sizeof (process_file_t))) == NULL)
        return NULL;

    if ((file->input_name = tmpnam(NULL)) == NULL)
    {
        process_file_free(&file);
        return NULL;
    }

    /* Temporary input name */
    tmp = calloc(strlen (file->input_name) + 3, 1);

    sprintf(tmp, "%s.c", file->input_name);

    file->input_name = tmp;

    /* Temporary output name */
    tmp = calloc(strlen (file->input_name) + 3, 1);

    sprintf(tmp, "%s.o", file->input_name);

    file->output_name = tmp;

    printf("[multi server] temporary output is : %s\n", file->output_name);

    file->result = NULL;

    return file;
}
