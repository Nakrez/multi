#include <share/utils.h>

unsigned zero_strlen(char *str)
{
    if (str)
        return strlen(str);
    else
        return 0;
}

int neg_strlen(const char *str)
{
    if (str)
        return strlen(str);
    else
        return -1;
}

char *read_fd(int fd)
{
    int read_byte = 0;
    int pos = 0;

    char temp_buf[PIPE_BUF];
    char *buf = NULL;

    while ((read_byte = read(fd, temp_buf, PIPE_BUF)) > 0)
    {
        buf = realloc(buf, zero_strlen(buf) + 2 + read_byte);
        strncpy(buf + pos, temp_buf, read_byte);
        pos += read_byte;
    }

    if (read_byte < 0)
    {
        free(buf);
        return NULL;
    }

    if (buf == NULL)
        return NULL;

    buf[pos] = 0;

    return buf;
}

int write_to_fd(int fd, const char *data, size_t n)
{
    /* The amount of byte left to write */
    size_t left_byte = n;
    /* The amount of byte written */
    size_t written_byte;

    while (left_byte > 0)
    {
        /* Try to write left byte */
        if ((written_byte = write(fd, data, left_byte)) <= 0)
            return -1;

        /* Update values */
        left_byte -= written_byte;
        data += written_byte;
    }

    return 0;
}

