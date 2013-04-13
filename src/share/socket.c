#include <share/socket.h>

int send_file(int socket_fd, const char *input_name)
{
    FILE* file = NULL;

    int read_bytes = 1;

    char buffer[1024];

    if ((file = fopen(input_name, "r")) == NULL)
    {
        printf("Cannot open file: %s", input_name);
        return -1;
    }

    while (read_bytes)
    {
        read_bytes = fread(buffer, 1, 1024, file);
        send(socket_fd, buffer, read_bytes, 0);
    }

    fclose(file);
}

int recv_file(int socket_fd, const char *output_name)
{

}
