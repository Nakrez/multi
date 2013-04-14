#include <share/socket.h>

/**
** @brief Write buffer @a data of size @a n in a file descriptor @a fd
**
** @param fd    The file descriptor where you want to write @a data
** @param data  The data you want to write in @a fd
** @param n     The size in byte you want to write in @a fd
**
** @return      0 if everything went well
                -1 else
*/
static int write_to_fd(int fd, const char *data, size_t n)
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

/**
** @brief Get the size of a file @a file
**
** @param file  The file you want to know the size
**
** @return      The size of the file @a file
*/
static size_t get_file_size(FILE *file)
{
    /*
    FIXME : Save the previous position from the file an restore it
    Needed since we are not sure that the cursor was at the begining
    */
    size_t size;

    /* Seek to the end of the file */
    fseek(file, 0L, SEEK_END);

    /* Get the size */
    size = ftell(file);

    /* Go back to the begining */
    fseek(file, 0L, SEEK_SET);

    return size;
}

int send_file(int socket_fd, const char *input_name)
{
    FILE* file = NULL;

    int read_bytes = 0;
    int file_size = 0;

    char buffer[1024];

    /* Open the input file */
    if ((file = fopen(input_name, "r")) == NULL)
    {
        ERROR_MSG("Cannot open file: %s", input_name);
        return -1;
    }

    /* Get the size of the file */
    file_size = get_file_size(file);

    /* Sending file size to server */
    write_to_fd(socket_fd, (char *)&file_size, sizeof (int));

    do
    {
        /* Read from input file */
        read_bytes = fread(buffer, 1, 1024, file);

        /* Send the buffer read to the fd */
        if (write_to_fd(socket_fd, buffer, read_bytes))
        {
            fclose(file);
            return -2;
        }

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

    /* Open the output file */
    if ((file = fopen(output_name, "w")) == NULL)
    {
        ERROR_MSG("Cannot open file: %s\n", output_name);
        return -1;
    }

    /* Get the file size to read from socket */
    if (read(socket_fd, (char *)&bytes_to_read, sizeof (int)) != 4)
    {
        ERROR_MSG("Cannot retrieve file size\n");
        return -2;
    }

    do
    {
        /* Read data from socket */
        read_bytes = read(socket_fd, buffer, 1024);

        /* Write read byte to the file */
        fwrite(buffer, 1, read_bytes, file);

        /* Update byte left to read */
        bytes_to_read -= read_bytes;

    } while (bytes_to_read);

    fclose(file);

    return 0;
}

int create_server_socket(int port)
{
    int socket_fd;
    /* Use for reuse socket */
    int yes = 1;

    struct sockaddr_in serv_addr;

    /* Create the socket */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");
        return -1;
    }

    /* Set reusable socket property */
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) < 0)
    {
        ERROR_MSG("Error: Can not set REUSEADDR property to socket\n");
        close(socket_fd);
        return -1;
    }

    /* Configure socket details */
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = 0;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;

    /* Bind socket */
    if (bind(socket_fd,
             (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) == -1)
    {
        ERROR_MSG("Error: Can not bind socket\n");
        close(socket_fd);
        return -1;
    }

    /* Listen for client */
    if (listen(socket_fd, SOCKET_QUEUE) == -1)
    {
        ERROR_MSG("Error: Socket can not listen\n");
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}
