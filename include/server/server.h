#include <netinet/in.h>
#include <stdint.h>
#include <sys/socket.h>

#include "client/client.h"

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
    socklen_t addr_len;
} Server;

int server_init(Server *server, uint16_t server_port);
int server_accept(Server *server, Client *client);
void server_run(Server *server);
void server_broadcast(Server *server, Client *sender, const char *msg);
void server_close(Server *server);

