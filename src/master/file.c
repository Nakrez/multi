#include <master/file.h>

multi_file_t *multi_file_new()
{
    multi_file_t *file = NULL;

    if ((file = malloc(sizeof(multi_file_t))) == NULL)
        return NULL;

    file->input_file = NULL;
    file->output_file = NULL;
    file->language = UNKNOWN;

    return file;
}

void multi_file_free(multi_file_t **file)
{
    free(*file);

    *file = NULL;
}
