#include <deamon/file.h>

void process_file_free(process_file_t **file)
{
    if (!*file)
        return;

    if ((*file)->input_name)
        free((*file)->input_name);

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

    tmp = calloc(strlen (file->input_name) + 3, 1);

    sprintf(tmp, "%s.c", file->input_name);

    file->input_name = tmp;

    if ((file->output_name = tmpnam(NULL)) == NULL)
    {
        process_file_free(&file);
        return NULL;
    }

    return file;
}
