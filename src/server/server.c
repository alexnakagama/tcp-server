#include <netinet/in.h>
#include <server/server.h>
#include <sys/socket.h>
#include <unistd.h>

/* This function configures a socket TCP so it acts as a server
    * Parameters: Server *server, uint16_t server_port (pointer to a server, unsigned int of a server port)
    * Returns: int
    *
    * All TCP servers in C are: socket -> bind -> listen -> accept
*/
int server_init(Server *server, uint16_t server_port) {
    if (!server) return -1;

    // Creates the socket TCP
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == 1) return -1;

    // Configures the server address
    // IPv4, port, accept connections in all IPs of the PC
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(server_port);
    server->addr.sin_addr.s_addr = INADDR_ANY;

    // bind() tells the OS this socket will use this IP and this port
    // assigns an address to the socket
    if (bind(server->fd, (struct sockaddr *)&server->addr, sizeof(server->addr)) < 0) {
        return -1;
    }

    if (listen(server->fd, SOMAXCONN) < 0) return -1;

    return 0;
}

int server_accept(Server *server, Client *client) {
}

void server_run(Server *server) {

}

void server_broadcast(Server *server, Client *sender, const char *msg) {

}

void server_close(Server *server) {
    if (!server) return;   

    close(server->fd);
}
