/**
 * @brief Languages supported by Multi
 * @date 12/04/2013
 * @author Baptiste COVOLATO <b.covolat@gmail.com>
 */

#ifndef LANGAGE_H
# define LANGAGE_H

# include <string.h>

typedef enum
{
    C,
    CXX,
    UNKNOWN
} e_language;

/**
** @brief Extract language from filename (based on extension)
**
** @param   filename    The filename from which you want to extract the
                        language
**
** @return  The language of the input file
*/
e_language extract_language(char *filename);

/* FIXME: doc */
char *get_compiler(e_language lang);

#endif /* !LANGAGE_H */
