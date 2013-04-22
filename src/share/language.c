#include <share/language.h>

static char *compilers_lang[] =
{
    "gcc",
    "g++"
};

static int is_c_source(char *filename)
{
    int len = strlen(filename);

    return len > 2 && !strcmp(filename + len - 2, ".c");
}

e_language extract_language(char *filename)
{
    if (is_c_source(filename))
        return C;

    return UNKNOWN;
}

char *get_compiler(e_language lang)
{
    if (lang == UNKNOWN)
        return NULL;

    return compilers_lang[lang];
}
