#include <share/socket.h>

static int write_to_fd(int fd, const char *data, size_t n)
{
    size_t left_byte = n;
    size_t written_byte;

    while (left_byte > 0)
    {
        if ((written_byte = write(fd, data, left_byte)) <= 0)
            return -1;

        left_byte -= written_byte;
        data += written_byte;
    }

    return left_byte;
}

static size_t get_file_size(FILE *file)
{
    size_t size;

    fseek(file, 0L, SEEK_END);

    size = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return size;
}

int send_file(int socket_fd, const char *input_name)
{
    FILE* file = NULL;

    int read_bytes = 0;
    int file_size = 0;

    char buffer[1024];

    if ((file = fopen(input_name, "r")) == NULL)
    {
        printf("Cannot open file: %s", input_name);
        return -1;
    }

    file_size = get_file_size(file);

    // Sending file size to server
    write_to_fd(socket_fd, (char *)&file_size, sizeof (int));

    do
    {
        read_bytes = fread(buffer, 1, 1024, file);
        if (write_to_fd(socket_fd, buffer, read_bytes))
            printf("Error writting file");
    } while (read_bytes);

    fclose(file);

    return 0;
}

int recv_file(int socket_fd, const char *output_name)
{
    FILE* file = NULL;

    int read_bytes = 0;

    char buffer[1024];

    if ((file = fopen(output_name, "w")) == NULL)
    {
        printf("Cannot open file: %s", output_name);
        return -1;
    }

    do
    {
        read_bytes = read(socket_fd, buffer, 1024);
        fwrite(buffer, 1, read_bytes, file);
    } while (read_bytes);

    fclose(file);

    return 0;
}
