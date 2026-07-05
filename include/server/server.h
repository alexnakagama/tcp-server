#include <netinet/in.h>
#include <sys/socket.h>

/*
    * In UNIX like os everything is treated as a file including:
    * - Regular files
    * - Sockets
    * - Pipes
    * - Terminals
    * - Devices
    *
    * A file descriptor is simply an integer that identifies one of these open resources
*/

typedef struct Server {
    int fd; // fd = file descriptor
    struct sockaddr_in addr;
} Server;
