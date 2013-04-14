#include <unistd.h>

#include <master/usage.h>
#include <master/client.h>


int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        usage();
        return 0;
    }

    return launch_client(argc, argv);
}
