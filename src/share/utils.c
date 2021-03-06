#include <share/utils.h>

unsigned count_occurence(char *str, char c)
{
    unsigned count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        if (*str == c)
            ++count;

        ++str;
    }

    return count;
}

unsigned zero_strlen(char *str)
{
    if (str)
        return strlen(str);
    else
        return 0;
}

int neg_strlen(const char *str)
{
    int len = -1;

    if (str)
        len = strlen(str);
    else
        return -1;

    if (len)
        return len;
    else
        return -1;
}

int read_fd(int fd, int size, char **buf)
{
    int read_byte = 0;
    int pos = 0;

    while ((read_byte = read(fd, *buf + pos, size - read_byte)) > 0)
    {
        pos += read_byte;
    }

    if (pos != size || read_byte < 0)
        return -1;

    buf[pos] = 0;

    return 0;
}

char *read_all_fd(int fd)
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
    int left_byte = n;
    /* The amount of byte written */
    int written_byte;

    while (left_byte > 0)
    {
        /* Try to write left byte */
        if ((written_byte = write(fd, data, left_byte)) <= 0)
            return -1;

        if (written_byte <= 0)
            break;

        /* Update values */
        left_byte -= written_byte;
        data += written_byte;
    }

    return 0;
}
