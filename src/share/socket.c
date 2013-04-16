#include <share/socket.h>

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

    /* FIXME optimise with PIPE_BUF */
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
    if ((write_to_fd(socket_fd, (char *)&file_size, sizeof (int))) == -1)
        return -2;

    do
    {
        /* Read from input file */
        read_bytes = fread(buffer, 1, 1024, file);

        /* Send the buffer read to the fd */
        if (write_to_fd(socket_fd, buffer, read_bytes) == -1)
        {
            fclose(file);
            return -3;
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

    /* FIXME optimise with PIPE_BUF */
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
        fclose(file);
        return -2;
    }

    do
    {
        /* Read data from socket */
        if ((read_bytes = read(socket_fd, buffer, 1024)) < 0)
        {
            fclose(file);
            return -3;
        }

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

int create_client_socket(const char *addr, int port)
{
    int socket_fd;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Get information on host */
    if ((server = gethostbyname(addr)) == NULL)
    {
        ERROR_MSG("ERROR: host %s can not be reached\n", addr);
        return -1;
    }

    /* Create socket */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ERROR_MSG("Error: Can not create socket\n");
        return -1;
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr_list[0],
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);

    serv_addr.sin_port = htons(port);

    /* Connect to the server */
    if (connect(socket_fd,
        (struct sockaddr *)&serv_addr,
        sizeof (serv_addr)) < 0)
    {
        ERROR_MSG("Error: Can not connect to the host: %s\n", addr);
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

int send_compile_result(int fd, compile_result_t *result)
{
    const int stdout_size = neg_strlen(result->std_out) + 1;
    const int stderr_size = neg_strlen(result->std_err) + 1;

    if ((write_to_fd(fd, (char *)&result->status, sizeof (int))) == -1)
        return -1;

    if ((write_to_fd(fd, (char *)&stdout_size, sizeof (int))) == -1)
        return -1;

    if (stdout_size)
    {
        if ((write_to_fd(fd, result->std_out, stdout_size)) == -1)
            return -1;
    }

    if ((write_to_fd(fd, (char *)&stderr_size, sizeof (int))) == -1)
        return -1;

    if (stderr_size)
    {
        if ((write_to_fd(fd, result->std_err, stderr_size)) == -1)
            return -1;
    }

    return 0;
}

compile_result_t *recv_compile_result(int fd)
{
    compile_result_t *result = NULL;

    int bytes_to_read = 0;
    int pos = 0;
    int n = 0;

    if ((result = compile_result_new()) == NULL)
        return NULL;

    /* Read the return status of compiler*/
    TREAT_ERROR(read(fd, (char *)&result->status, sizeof (int)) != sizeof (int));

    /* Read the size of std_out */
    TREAT_ERROR(read(fd, (char *)&bytes_to_read, sizeof (int)) != sizeof (int));

    if (bytes_to_read)
    {
        TREAT_ERROR((result->std_out = calloc(bytes_to_read, 1)) == NULL);

        /* Read std_out */
        while ((n = read(fd, result->std_out + pos, PIPE_BUF)) <= 0)
        {
            pos += n;
            if (pos == bytes_to_read)
                break;
        }

        /* Check fd error */
        TREAT_ERROR(n < 0);

        n = 0;
        pos = 0;
    }

    /* Read size of std_err */
    TREAT_ERROR(read(fd, (char *)&bytes_to_read, sizeof (int)) != sizeof (int));

    if (bytes_to_read)
    {
        TREAT_ERROR((result->std_err = calloc(bytes_to_read, 1)) == NULL);

        /* Read std_err */
        while ((n = read(fd, result->std_err + pos, PIPE_BUF)) <= 0)
        {
            pos += n;
            if (pos == bytes_to_read)
                break;
        }

        /* Check fd error */
        TREAT_ERROR(n < 0);
    }

    return result;

error:
    printf("Error in recv_compile_result()\n");
    compile_result_free(&result);
    return NULL;
}
