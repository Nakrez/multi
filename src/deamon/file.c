#include <deamon/file.h>

void process_file_free(process_file_t **file)
{
    if (!*file)
        return;

    /* output_name do not need to be free because it contains tmpnam value */

    free((*file)->input_name);
    compile_result_free(&(*file)->result);

    free(*file);
    *file = NULL;
}

/* static int file_exists(const char *filename) */
/* { */
/*     FILE *file = NULL; */
/*  */
/*     if ((file = fopen(filename, "r"))) */
/*     { */
/*         fclose(file); */
/*         return 1; */
/*     } */
/*  */
/*     return 0; */
/* } */
/*  */
/* static int touch(const char *filename) */
/* { */
/*     FILE *f = fopen(filename, "w"); */
/*  */
/*     if (f) */
/*     { */
/*         fclose(f); */
/*         return 1; */
/*     } */
/*  */
/*     return 0; */
/* } */

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
