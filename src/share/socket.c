#include <share/socket.h>

int send_file(int socket_fd, const char *input_name)
{
    FILE* file = NULL;

    int read_bytes = 0;

    char buffer[1024];

    if ((file = fopen(input_name, "r")) == NULL)
    {
        printf("Cannot open file: %s", input_name);
        return -1;
    }

    do
    {
        read_bytes = fread(buffer, 1, 1024, file);
        write(socket_fd, buffer, read_bytes);
    } while (read_bytes);

    fclose(file);

    return 0;
}

int recv_file(int socket_fd, const char *output_name)
{
    FILE* file = NULL;

    int read_bytes = 0;
    int bytes_to_read = 0;

    char buffer[1024];

    if ((file = fopen(output_name, "w")) == NULL)
    {
        printf("Cannot open file: %s", output_name);
        return -1;
    }

    if (read(socket_fd, (char *)&bytes_to_read, sizeof (int)) != 4)
    {
        printf("Cannot retrieve file size\n");
        return -1;
    }

    do
    {
        read_bytes = read(socket_fd, buffer, 1024);
        fwrite(buffer, 1, read_bytes, file);
        bytes_to_read -= read_bytes;
    } while (bytes_to_read);

    fclose(file);

    return 0;
}
